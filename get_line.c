#include "shell.h"
/**
 * our_input_buf - buffers chained commands
 * @info: parameter struct
 * @custom_buf: address of buffer
 * @custom_len: address of len var
 *
 * Return: bytes read
 */
ssize_t our_input_buf(our_info_t *info, char **our_buf,
size_t *our_len)
{
	ssize_t q = 0;
	size_t len_z = 0;

	if (!*our_len) /* if nothing left in the buffer, fill it */
	{
		/* our_bfree((void **)info->custom_cmd_buf); */
		free(*our_buf);
		*our_buf = NULL;
		signal(SIGINT, our_sigintHandler);
#if USE_GETLINE
		q = getline(our_buf, &len_z, stdin);
#else
		q = our_getline(info, our_buf, &len_z);
#endif
		if (q > 0)
		{
			if ((*our_buf)[q - 1] == '\n')
			{
				(*our_buf)[q - 1] = '\0'; /* remove trailing newline */
				q--;
			}
			info->our_linecount_flag = 1;
			our_remove_comments(*our_buf);
			our_build_history_list(info, *our_buf, info->our_histcount++);
			/* if (_strchr(*our_buf, ';')) is this a command chain? */
			{
				*our_len = q;
				info->our_cmd_buf = our_buf;
			}
		}
	}
	return (q);
}

/**
 * our_get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t our_get_input(our_info_t *info)
{
	static char *our_buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t q = 0;
	char **buf_z = &(info->our_arg), *z;

	our_putchar(OUR_BUF_FLUSH);
	q = our_input_buf(info, &our_buf, &len);
	if (q == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		z = our_buf + i;
		our_check_chain(info, our_buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (our_is_chain(info, our_buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->our_cmd_buf_type = CMD_NORM;
		}
		*buf_z = z; /* pass back pointer to current command position */
		return (our_strlen(z)); /* return length of current command */
	}

	*buf_z = our_buf;
	return (q); /* return length of buffer from our_getline() */
}

/**
 * our_read_buf - reads a buffer
 * @info: parameter struct
 * @our_buf: buffer
 * @i: size
 *
 * Return: q
 */
ssize_t our_read_buf(our_info_t *info, char *our_buf, size_t *i)
{
	ssize_t q = 0;

	if (*i)
		return (0);
	q = read(info->readFileDescriptor, our_buf, READ_BUF_SIZE);
	if (q >= 0)
		*i = q;
	return (q);
}

/**
 * our_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int our_getline(our_info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t q = 0, s = 0;
	char *z = NULL, *new_z = NULL, *c;

	z = *ptr;
	if (z && length)
		s = *length;
	if (i == l)
		i = l = 0;

	q = our_read_buf(info, buf, &l);
	if (q == -1 || (q == 0 && l == 0))
		return (-1);
	c = _our_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : l;
	new_z = our_realloc(z, s, s ? s + k : k + 1);
	if (!new_z) /* MALLOC FAILURE! */
		return (z ? free(z), -1 : -1);
	if (s)
		_our_strncat(new_z, buf + i, k - i);
	else
		_our_strncpy(new_z, buf + i, k - i + 1);
	s += k - i;
	i = k;
	z = new_z;
	if (length)
		*length = s;
	*ptr = z;
	return (s);
}

/**
 * our_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void our_sigintHandler(__attribute__((unused))int sig_num)
{
	our_puts("\n");
	our_puts("jecinta.joseph$ ");
	our_putchar(OUR_BUF_FLUSH);
}

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
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*our_len) /* if nothing left in the buffer, fill it */
	{
		/* our_bfree((void **)info->custom_cmd_buf); */
		free(*our_buf);
		*our_buf = NULL;
		signal(SIGINT, our_sigintHandler);
#if USE_GETLINE
		r = getline(our_buf, &len_p, stdin);
#else
		r = our_getline(info, our_buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*our_buf)[r - 1] == '\n')
			{
				(*our_buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->our_linecount_flag = 1;
			our_remove_comments(*our_buf);
			our_build_history_list(info, *our_buf, info->our_histcount++);
			/* if (_strchr(*our_buf, ';')) is this a command chain? */
			{
				*our_len = r;
				info->our_cmd_buf = our_buf;
			}
		}
	}
	return (r);
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
	ssize_t r = 0;
	char **buf_p = &(info->our_arg), *p;

	our_putchar(OUR_BUF_FLUSH);
	r = our_input_buf(info, &our_buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = our_buf + i;
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
		*buf_p = p; /* pass back pointer to current command position */
		return (our_strlen(p)); /* return length of current command */
	}

	*buf_p = our_buf;
	return (r); /* return length of buffer from our_getline() */
}

/**
 * our_read_buf - reads a buffer
 * @info: parameter struct
 * @our_buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t our_read_buf(our_info_t *info, char *our_buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readFileDescriptor, our_buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
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
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = our_read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _our_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = our_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_our_strncat(new_p, buf + i, k - i);
	else
		_our_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
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

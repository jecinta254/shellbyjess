#include "shell.h"

/**
 * our_is_chain - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int our_is_chain(our_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->our_cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->our_cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->our_cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * our_check_chain - checks if we
 * should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void our_check_chain(our_info_t *info,
char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->our_cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->our_cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * our_replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_alias(our_info_t *info)
{
	int i;
	our_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = our_node_starts_with(info->our_alias,
		info->our_argv[0], '=');
		if (!node)
			return (0);
		free(info->our_argv[0]);
		p = _our_strchr(node->str, '=');
		if (!p)
			return (0);
		p = our_strdup(p + 1);
		if (!p)
			return (0);
		info->our_argv[0] = p;
	}
	return (1);
}

/**
 * our_replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_vars(our_info_t *info)
{
	int i = 0;
	our_list_t *node;

	for (i = 0; info->our_argv[i]; i++)
	{
		if (info->our_argv[i][0] != '$' || !info->our_argv[i][1])
			continue;

		if (!our_strcmp(info->our_argv[i], "$?"))
		{
			our_replace_string(&(info->our_argv[i]),
				our_strdup(our_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!our_strcmp(info->our_argv[i], "$$"))
		{
			our_replace_string(&(info->our_argv[i]),
				our_strdup(our_convert_number(getpid(),
				10, 0)));
			continue;
		}
		node = our_node_starts_with(info->our_env,
		&info->our_argv[i][1], '=');
		if (node)
		{
			our_replace_string(&(info->our_argv[i]),
				our_strdup(_our_strchr(node->str, '=') + 1));
			continue;
		}
		our_replace_string(&info->our_argv[i], our_strdup(""));
	}
	return (0);
}

/**
 * our_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int our_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

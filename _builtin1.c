#include "shell.h"
/**
 * _our_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _our_history(our_info_t *info)
{
	our_print_list(info->our_history);
	return (0);
}
/**
 * unset_our_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_our_alias(our_info_t *info, char *str)
{
	char *z, c;
	int rt;

	z = _our_strchr(str, '=');
	if (!z)
		return (1);
	c = *z;
	*z = 0;
	rt = our_delete_node_at_index(&(info->our_alias),
		our_get_node_index(info->our_alias,
		our_node_starts_with(info->our_alias, str, -1)));
	*z = c;
	return (rt);
}
/**
 * set_our_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_our_alias(our_info_t *info, char *str)
{
	char *z;

	z = _our_strchr(str, '=');
	if (!z)
		return (1);
	if (!*++z)
		return (unset_our_alias(info, str));

	unset_our_alias(info, str);
	return (our_add_node_end(&(info->our_alias), str, 0) == NULL);
}
/**
 * print_our_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_our_alias(our_list_t *node)
{
	char *z = NULL, *a = NULL;

	if (node)
	{
		z = _our_strchr(node->str, '=');
		for (a = node->str; a <= z; a++)
			our_putchar(*a);
		our_putchar('\'');
		our_puts(z + 1);
		our_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _our_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _our_alias(our_info_t *info)
{
	int i = 0;
	char *z = NULL;
	our_list_t *node = NULL;

	if (info->our_argc == 1)
	{
		node = info->our_alias;
		while (node)
		{
			print_our_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->our_argv[i]; i++)
	{
		z = _our_strchr(info->our_argv[i], '=');
		if (z)
			set_our_alias(info, info->our_argv[i]);
		else
			print_our_alias(our_node_starts_with
			(info->our_alias, info->our_argv[i], '='));
	}

	return (0);
}

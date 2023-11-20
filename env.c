#include "shell.h"
/**
 * _our_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _our_env(our_info_t *info)
{
	our_print_list_str(info->our_env);
	return (0);
}

/**
 * getEnvironments - gets the value of a custom environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *getEnvironments(our_info_t *info, const char *name)
{
	our_list_t *node = info->our_env;
	char *p;

	while (node)
	{
		p = our_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _our_setenv - Initialize a new our environment variable,
 *                  or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _our_setenv(our_info_t *info)
{
	if (info->our_argc != 3)
	{
		_our_eputs("bad number of arguments\n");
		return (1);
	}
	if (our_setenv(info, info->our_argv[1], info->our_argv[2]))
		return (0);
	return (1);
}

/**
 * _our_unsetenv - Remove a our environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _our_unsetenv(our_info_t *info)
{
	int i;

	if (info->our_argc == 1)
	{
		_our_eputs("very very few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->our_argc; i++)
		our_unsetenv(info, info->our_argv[i]);
	return (0);
}

/**
 * populate_our_env_list - populates our env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_our_env_list(our_info_t *info)
{
	our_list_t *node = NULL;
	size_t i;

	for (i = 0;  environ[i]; i++)
		our_add_node_end(&node,  environ[i], 0);
	info->our_env = node;
	return (0);
}

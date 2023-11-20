#include "shell.h"
/**
 * our_get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **our_get_environ(our_info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = our_list_to_strings(info->our_env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * custom_unsetenv - Remove our environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string custom env var property
 */
int our_unsetenv(our_info_t *info, char *var)
{
	our_list_t *node = info->our_env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = our_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = our_delete_node_at_index(&(info->our_env), i);
			i = 0;
			node = info->our_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * our_setenv - Initialize our new environment variable,
 *                 or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string custom env var property
 * @value: the string custom env var value
 * Return: Always 0
 */
int our_setenv(our_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	our_list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(our_strlen(var) + our_strlen(value) + 2);
	if (!buf)
		return (1);
	our_strcpy(buf, var);
	our_strcat(buf, "=");
	our_strcat(buf, value);
	node = info->our_env;
	while (node)
	{
		p = our_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	our_add_node_end(&(info->our_env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

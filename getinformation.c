#include "shell.h"

/**
 * our_clear_info - initializes info_t struct
 * @info: struct address
 */
void our_clear_info(our_info_t *info)
{
	info->our_arg = NULL;
	info->our_argv = NULL;
	info->our_path = NULL;
	info->our_argc = 0;
}
/**
 * our_set_info - initializes info_t struct
 * @info: struct address
 * @our_av: our argument vector
 */
void our_set_info(our_info_t *info, char **our_av)
{
	int i = 0;

	info->our_fname = our_av[0];
	if (info->our_arg)
	{
		info->our_argv = our_strtow(info->our_arg, " \t");
		if (!info->our_argv)
		{
			info->our_argv = malloc(sizeof(char *) * 2);
			if (info->our_argv)
			{
				info->our_argv[0] = our_strdup(info->our_arg);
				info->our_argv[1] = NULL;
			}
		}
		for (i = 0; info->our_argv && info->our_argv[i]; i++)
			;
		info->our_argc = i;
		our_replace_alias(info);
		our_replace_vars(info);
	}
}

/**
 * our_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void our_free_info(our_info_t *info, int all)
{
	our_ffree(info->our_argv);
	info->our_argv = NULL;
	info->our_path = NULL;

	if (all)
	{
		if (!info->our_cmd_buf)
			free(info->our_arg);
		if (info->our_env)
			our_free_list(&(info->our_env));
		if (info->our_history)
			our_free_list(&(info->our_history));
		if (info->our_alias)
			our_free_list(&(info->our_alias));
		our_ffree(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->our_cmd_buf);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		our_putchar(OUR_BUF_FLUSH);
	}
}

#include "shell.h"

/**
 * our_hsh - main shell loop
 * @info: the parameter & return info struct
 * @our_av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int our_hsh(our_info_t *info, char **our_av)
{
	ssize_t our_r = 0;
	int our_builtin_ret = 0;

	while (our_r != -1 && our_builtin_ret != -2)
	{
		our_clear_info(info);
		if (ourInteractive(info))
			our_puts("jecinta.joseph$: ");
		_our_eputchar(OUR_BUF_FLUSH);
		our_r = our_get_input(info);
		if (our_r != -1)
		{
			our_set_info(info, our_av);
			our_builtin_ret = our_find_builtin(info);
			if (our_builtin_ret == -1)
				our_find_cmd(info);
		}
		else if (ourInteractive(info))
			our_putchar('\n');
		our_free_info(info, 0);
	}
	our_write_history(info);
	our_free_info(info, 1);
	if (!ourInteractive(info) && info->status)
		exit(info->status);
	if (our_builtin_ret == -2)
	{
		if (info->errorNumber == -1)
			exit(info->status);
		exit(info->errorNumber);
	}
	return (our_builtin_ret);
}

/**
 * our_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int our_find_builtin(our_info_t *info)
{
	int i, our_built_in_ret = -1;
	our_builtin_table our_builtintbl[] = {
		{"exit", exit_Shell},
		{"env", _our_env},
		{"help", show_Help},
		{"history",  _our_history},
		{"setenv", _our_setenv},
		{"unsetenv", _our_unsetenv},
		{"cd", change_Directory},
		{"alias",  _our_alias},
		{NULL, NULL}
	};

	for (i = 0; our_builtintbl[i].type; i++)
		if (our_strcmp(info->our_argv[0], our_builtintbl[i].type) == 0)
		{
			info->line_count++;
			our_built_in_ret = our_builtintbl[i].func(info);
			break;
		}
	return (our_built_in_ret);
}

/**
 * our_find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void our_find_cmd(our_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->our_path = info->our_argv[0];
	if (info->our_linecount_flag == 1)
	{
		info->line_count++;
		info->our_linecount_flag = 0;
	}
	for (i = 0, k = 0; info->our_arg[i]; i++)
		if (!ourDelimiter(info->our_arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = our_find_path(info,
	getEnvironments(info, "PATH="), info->our_argv[0]);
	if (path)
	{
		info->our_path = path;
		our_fork_cmd(info);
	}
	else
	{
		if ((ourInteractive(info) ||
		getEnvironments(info, "PATH=")
			|| info->our_argv[0][0] == '/') &&
			our_is_cmd(info, info->our_argv[0]))
			our_fork_cmd(info);
		else if (*(info->our_arg) != '\n')
		{
			info->status = 127;
			our_print_error(info, "not found\n");
		}
	}
}

/**
 * our_fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void our_fork_cmd(our_info_t *info)
{
	pid_t our_child_pid;

	our_child_pid = fork();
	if (our_child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (our_child_pid == 0)
	{
		if (execve(info->our_path, info->our_argv,
		our_get_environ(info)) == -1)
		{
			our_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				our_print_error(info, "Permission decline\n");
		}
	}
}

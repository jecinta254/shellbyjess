#include "shell.h"
/**
 * _our_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _our_exit(our_info_t *info)
{
	int exit_check;

	if (info->our_argv[1])
	{
		exit_check = _our_erratoi(info->our_argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			our_print_error(info, "bad number: ");
			_our_eputs(info->our_argv[1]);
			_our_eputchar('\n');
			return (1);
		}
		info->errorNumber = _our_erratoi(info->our_argv[1]);
		return (-2);
	}
	info->errorNumber = -1;
	return (-2);
}
/**
 * _our_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _our_cd(our_info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		our_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->our_argv[1])
	{
		target_dir = getEnvironmentV(info, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((target_dir = getEnvironmentV(info, "PWD=")) ?
				target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (our_strcmp(info->our_argv[1], "-") == 0)
	{
		if (!getEnvironmentV(info, "OLDPWD="))
		{
			our_puts(current_dir), our_putchar('\n');
			return (1);
		}
		our_puts(getEnvironmentV(info, "OLDPWD=")), our_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((target_dir = getEnvironmentV(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info->our_argv[1]);
	if (chdir_ret == -1)
	{
		our_print_error(info, "cd not working ");
		_our_eputs(info->our_argv[1]), _our_eputchar('\n');
	}
	else
	{
		our_setenv(info, "OLDPWD", getEnvironmentV(info, "PWD="));
		our_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _our_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _our_help(our_info_t *info)
{
	char **arg_array;

	arg_array = info->our_argv;
	our_puts("HELP!! function is yet implemented \n");
	if (0)
		our_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

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
	char *cdir, *tdir, buffer[1024];
	int chdir_rt;

	cdir = getcwd(buffer, 1024);
	if (!cdir)
		our_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->our_argv[1])
	{
		tdir = getEnvironments(info, "HOME=");
		if (!tdir)
			chdir_rt = /* TODO: what should this be? */
				chdir((tdir = getEnvironments(info, "PWD=")) ?
				tdir : "/");
		else
			chdir_rt = chdir(tdir);
	}
	else if (our_strcmp(info->our_argv[1], "-") == 0)
	{
		if (!getEnvironments(info, "OLDPWD="))
		{
			our_puts(cdir), our_putchar('\n');
			return (1);
		}
		our_puts(getEnvironments(info, "OLDPWD=")), our_putchar('\n');
		chdir_rt = /* TODO: what should this be? */
			chdir((tdir = getEnvironments(info, "OLDPWD=")) ? tdir : "/");
	}
	else
		chdir_rt = chdir(info->our_argv[1]);
	if (chdir_rt == -1)
	{
		our_print_error(info, "cd not working ");
		_our_eputs(info->our_argv[1]), _our_eputchar('\n');
	}
	else
	{
		our_setenv(info, "OLDPWD", getEnvironments(info, "PWD="));
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
	char **argArray;

	argArray = info->our_argv;
	our_puts("HELP!! function is yet implemented \n");
	if (0)
		our_puts(*argArray); /* temp att_unused workaround */
	return (0);
}

#include "shell.h"
/**
 * exit_Shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shellInfo.argv[0] != "exit"
 */
int exit_Shell(our_info_t *info)
{
	int exiting;

	if (info->our_argv[1]) /* If there is an exit argument */
	{
		exiting = _our_erratoi(info->our_argv[1]);
		if (exiting == -1)
		{
			info->status = 2;
			our_print_error(info, "Bad number: ");
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
 * change_Directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_Directory(our_info_t *info)
{
	char *cDir, *nDir, buffer[1024];
	int chdirReturn;

	cDir = getcwd(buffer, 1024);
	if (!cDir)
		our_puts("TODO: >>getcwd on failure emsg<<\n");
	if (!info->our_argv[1])
	{
		nDir = getEnvironments(info, "HOME=");
		if (!nDir)
			chdirReturn = /* TODO: what should this be? */
				chdir((nDir = getEnvironments(info, "PWD=")) ? nDir : "/");
		else
			chdirReturn = chdir(nDir);
	}
	else if (our_strcmp(info->our_argv[1], "-") == 0)
	{
		if (!getEnvironments(info, "OLDPWD="))
		{
			our_puts(cDir);
			our_putchar('\n');
			return (1);
		}
		our_puts(getEnvironments(info, "OLDPWD=")), our_putchar('\n');
		chdirReturn = /* TODO: what should this be? */
			chdir((nDir = getEnvironments(info, "OLDPWD=")) ? nDir : "/");
	}
	else
		chdirReturn = chdir(info->our_argv[1]);
	if (chdirReturn == -1)
	{
		our_print_error(info, "can't cd to ");
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
 * show_Help - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int show_Help(our_info_t *info)
{
	char **argArray;

	argArray = info->our_argv;
	our_puts("Help!! function is yet implemented \n");
	if (0)
		our_puts(*argArray);
	return (0);
}

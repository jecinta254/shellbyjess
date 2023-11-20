#include "shell.h"
/**
 * exitShell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shellInfo.argv[0] != "exit"
 */
int exitShell(our_info_t *info)
{
	int exitCheck;

	if (info->our_argv[1]) /* If there is an exit argument */
	{
		exitCheck = _our_erratoi(info->our_argv[1]);
		if (exitCheck == -1)
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
 * changeDirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int changeDirectory(our_info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirReturn;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		our_puts("TODO: >>getcwd on failure emsg<<\n");
	if (!info->our_argv[1])
	{
		newDir = getEnvironmentV(info, "HOME=");
		if (!newDir)
			chdirReturn = /* TODO: what should this be? */
				chdir((newDir = getEnvironmentV(info, "PWD=")) ? newDir : "/");
		else
			chdirReturn = chdir(newDir);
	}
	else if (our_strcmp(info->our_argv[1], "-") == 0)
	{
		if (!getEnvironmentV(info, "OLDPWD="))
		{
			our_puts(currentDir);
			our_putchar('\n');
			return (1);
		}
		our_puts(getEnvironmentV(info, "OLDPWD=")), our_putchar('\n');
		chdirReturn = /* TODO: what should this be? */
			chdir((newDir = getEnvironmentV(info, "OLDPWD=")) ? newDir : "/");
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
		our_setenv(info, "OLDPWD", getEnvironmentV(info, "PWD="));
		our_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int showHelp(our_info_t *info)
{
	char **argumentArray;

	argumentArray = info->our_argv;
	our_puts("Help!! function is yet implemented \n");
	if (0)
		our_puts(*argumentArray);
	return (0);
}

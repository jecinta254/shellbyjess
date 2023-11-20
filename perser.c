#include "shell.h"
/**
 * our_is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @our_path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int our_is_cmd(our_info_t *info, char *our_path)
{
	struct stat st;

	(void)info;
	if (!our_path || stat(our_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * our_dup_chars - duplicates characters
 * @our_pathstr: the PATH string
 * @our_start: starting index
 * @our_stop: stopping index
 * Return: pointer to new buffer
 */
char *our_dup_chars(char *our_pathstr, int our_start, int our_stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = our_start; i < our_stop; i++)
		if (our_pathstr[i] != ':')
			buf[k++] = our_pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * our_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @our_pathstr: the PATH string
 * @our_cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *our_find_path(our_info_t *info,
char *our_pathstr, char *our_cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!our_pathstr)
		return (NULL);
	if ((our_strlen(our_cmd) > 2) && our_starts_with(our_cmd, "./"))
	{
		if (our_is_cmd(info, our_cmd))
			return (our_cmd);
	}
	while (1)
	{
		if (!our_pathstr[i] || our_pathstr[i] == ':')
		{
			path = our_dup_chars(our_pathstr, curr_pos, i);
			if (!*path)
				our_strcat(path, our_cmd);
			else
			{
				our_strcat(path, "/");
				our_strcat(path, our_cmd);
			}
			if (our_is_cmd(info, path))
				return (path);
			if (!our_pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

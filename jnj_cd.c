#include "shell.h"

/**
 * cd_directory - changes current directory
 *
 */

void cd_directory(const char *path)
{
    if (chdir(path) != 0)
    {
        perror("cd");
    }
}

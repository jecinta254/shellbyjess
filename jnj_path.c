#include "shell.h"

/**
 * command_exists_path - fuction that defines the path
 *
 */

int command_exists_path(const char *command)
{
    char *paths = getenv("PATH");
    char *path_cpy = strdup(paths);
    char *token = strtok(path_cpy, ":");
    
    while (token != NULL)
    {
        char full_path[BUFFER_SIZE];
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_cpy);
            return (1);
        }

        token = strtok(NULL, ":");
    }

    free(path_cpy);
    return 0;
}

#include "shell.h"

int command_exists(const char *command) {
    return access(command, X_OK) == 0;
}

int jnj_path()
{
    char *path_s = getenv("PATH");

    if (path_s != NULL) {
        char *path_cp = strdup(path_s);
        char *token = strtok(path_cp, ":");
        
        while (token != NULL) {
            char command_paths[256];
            snprintf(command_paths, sizeof(command_paths), "%s/%s", token, "ls");

            if (command_exists(command_paths)) {
                printf("Command found: %s\n", command_paths);
            } else {
                printf("Command not found: %s\n", command_paths);
            }

            token = strtok(NULL, ":");
        }

        free(path_cp);
    }

    return 0;
}

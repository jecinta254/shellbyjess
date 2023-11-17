#include "shell.h"
#include "jnj_command_separator.c"

int main(void) {
    char command[BUFFER_SIZE];

    while (!exit_flag) {
        jnj_prompt();
        jnj_getline(command, sizeof(command));

        if (strncmp(command, "exit", 4) == 0) {
            int status = atoi(command + 5);
            printf("Exiting the shell with status %d.\n", status);
            exit_flag = 1;
            exit(status);
        } else if (strncmp(command, "env", 3) == 0) {
            run_env();
        } else if (strncmp(command, "setenv", 6) == 0) {
            // Implement setenv logic
        } else if (strncmp(command, "unsetenv", 8) == 0) {
            // Implement unsetenv logic
        } else if (strncmp(command, "cd", 2) == 0) {
            // Implement cd logic
        } else if (strncmp(command, ";", 1) == 0) {
            execute_commands(command + 1);
        } else if (strncmp(command, "&&", 2) == 0 || strncmp(command, "||", 2) == 0) {
            execute_logical_commands(command + 2);
        } else if (feof(stdin)) {
            jnj_print("\n");
            exit_flag = 1;
            break;
        } else if (command[0] != '\0' && command[0] != '\n') {
            jnj_execute(command);
        }
    }

    return 0;
}


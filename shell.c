#include "shell.h"
<<<<<<< HEAD
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
=======
/**
* main - the entry point of the shell program.
* Return: Always 0.
*/
int main(void)
{
char watho[BUFFER_SIZE];

if (isatty(fileno(stdin)))
{
while (true)
{
jnj_prompt();
jnj_readcmd(watho, sizeof(watho));
if (strcmp(watho, "exit\n") == 0)
{
break;
}
else if (strcmp(watho, "env\n") == 0)
{
jnj_envout();
}
else
{
jnj_execute2(watho);
}
if (feof(stdin))
{ jnj_print("\n");
break; }
if (watho[0] != '\0' && watho[0] != '\n')
{ jnj_execute(watho);
}
}
}
else
{
while (fgets(watho, sizeof(watho), stdin) != NULL)
{
watho[strcspn(watho, "\n")] = '\0';
if (watho[0] != '\0')
{
jnj_execute(watho);
}
}
}
return (0);
>>>>>>> f370579e2f12f2686767d18b721fe14323fc4b06
}

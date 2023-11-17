#include "shell.h"
int exit_flag = 0;

int main(void)
{
char command[BUFFER_SIZE];
while (!exit_flag)
{
jnj_prompt();
jnj_getline(command, sizeof(command));

if (strncmp(command, "exit", 4) == 0)
{
int status = atoi(command + 5);
exit_flag = 1;
exit(status);
}
else if (strncmp(command, "env", 3) == 0)
{
run_env();
}
else if (strncmp(command, "setenv", 6) == 0)
{ }
else if (strncmp(command, "unsetenv", 8) == 0)
{ }
else if (strncmp(command, "cd", 2) == 0)
{ }
else if (strstr(command, "&&") != NULL || strstr(command, "||") != NULL)
{
execute_logical_commands(command);
}
else if (feof(stdin))
{
jnj_print("\n");
exit_flag = 1;
break;
}
else if (command[0] != '\0' && command[0] != '\n')
{
jnj_execute(command);
} }
return (0);
}

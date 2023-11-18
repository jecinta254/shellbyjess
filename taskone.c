#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
/**
 * show_prompt - Display the prompt for user input.
 */
void show_prompt(void)
{
printf("#cisfun$ ");
}
/**
 * main - Main function where the shell logic is implemented.
 * Return: 0 on successful execution.
 */
int main(void)
{
char command[MAX_COMMAND_LENGTH];
pid_t mtoto_pid;

while (1)
{
show_prompt();
if (fgets(command, sizeof(command), stdin) == NULL)
{
printf("\n");
break;
}
command[strcspn(command, "\n")] = '\0';
if (strcmp(command, "exit") == 0)
{
break;
}
mtoto_pid = fork();
if (mtoto_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (mtoto_pid == 0)
{
execlp(command, command, (char *)NULL);
perror("exec");
exit(EXIT_FAILURE);
}
else
{
int status;
waitpid(mtoto_pid, &status, 0);

if (status != 0)
{
fprintf(stderr, "./shell: %s: command not found\n", command);
} } }
return (0);
}


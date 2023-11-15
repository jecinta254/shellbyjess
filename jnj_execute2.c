#include "shell.h"

/**
* jnj_execute2 - executes a command with arguments.
* @watho: The command to execute.
*/
void jnj_execute2(const char *watho)
{
char **argument_s;
char *token;
int status;
int arg_ment_count = 0;
char *delm = " \t\n";
pid_t mtoto_pid;

token = strtok((char *)watho, delm);
argument_s = malloc(sizeof(char *));

while (token)
{
argument_s = realloc(argument_s, (sizeof(char *) * (arg_ment_count + 2)));
argument_s[arg_ment_count] = strdup(token);
token = strtok(NULL, delm);
arg_ment_count++;

}

argument_s[arg_ment_count] = NULL;
mtoto_pid = fork();

if (mtoto_pid == 0)
{
if (execvp(argument_s[0], argument_s) == -1)
{
perror("Error");
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}

free(argument_s);
}


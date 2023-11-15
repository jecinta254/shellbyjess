#include "shell.h"

/**
 * jnj_execute - executes a command with arguments.
 * @watho: The command to execute.
 */
void jnj_execute2(const char *watho)
{
    char **argument_s;
    char *token;
    int status;
    int arg_ment_count = 0;
    char *delm = " ";
    pid_t mtoto_pid;

    token = strtok((char *)watho, delm);
    argument_s = malloc(sizeof(char *) * 2);

    while (token)
    {
        argument_s[arg_ment_count] = token;
        token = strtok(NULL, delm);
        arg_ment_count++;

        argument_s = realloc(argument_s, sizeof(char *) * (arg_ment_count+ 1));
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


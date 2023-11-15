#include "shell.h"

/**
 *jnj_execute3 - function that changes directory
 *
 */

void jnj_execute3(const char *watho)
{
    char **argument_s;
    char *token;
    int status;
    int arg_ument_count = 0;
    char *delm = " ";
    pid_t mtoto_pid;

    token = strtok((char *)watho, delm);
    argument_s = (char **)malloc(sizeof(char *));

    while (token)
    {
        argument_s[arg_ument_count] = strdup(token);
        token = strtok(NULL, delm);
        arg_ument_count++;

        argument_s = realloc(argument_s, sizeof(char *) * (arg_ument_count + 1));
    }

    argument_s[arg_ument_count] = NULL;
    mtoto_pid = fork();
    if (mtoto_pid == 0)
    {
        if (execve(argument_s[0], argument_s, environ) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }

    arg_ument_count = 0;
    free(argument_s);
}

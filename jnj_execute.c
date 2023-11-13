#include "shell.h"

void jnj_execute(const char *watho) {
        char *argument_s[1024];
        char *token;
        int status, arg_ument_count = 0;
        char *delm = (" ");
        pid_t mtoto_pid;

	token = strtok((char *)watho, delm);
	

	while (token) 
	{
	argument_s[arg_ument_count] = token;
	token = strtok(NULL, delm);
        arg_ument_count++;
        }
		argument_s[arg_ument_count] = NULL;
		mtoto_pid = fork();

        if (mtoto_pid == 0)
	{
               if (execve(argument_s[0], argument_s, NULL) == -1)
		 	perror("Error");
        }
	else 
	{

                wait(&status);
        }
        arg_ument_count = 0;
}

#include "shell.h"

/**
* run_env - it prints the environment variables.
*/

void run_env(void)
{
int i;

for (i = 0; environ[i] != NULL; i++)
{
printf("%s\n", environ[i]);
}
}

/**
* our_env - its the custom shell environment.
*
* Returns: 0 on success.
*/

int our_env(void)
{
char *buffer = NULL;
size_t len;
ssize_t read;

while (1)
{
printf("$ ");
read = getline(&buffer, &len, stdin);

if (read == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}

if (strcmp(buffer, "env\n") == 0)
{
run_env();
}
else if (strcmp(buffer, "exit\n") == 0)
{
break;
}
free(buffer);
}
return (0);
}

#include "shell.h"

/**
* jnj_readcmd - it reads a command from stdin.
* @watho: the buffer to store the command.
* @size: the size of the buffer.
*/

void jnj_readcmd(char *watho, size_t size)
{
if (fgets(watho, size, stdin) == NULL)
{
if (feof(stdin))
{
jnj_print("\n");
exit(EXIT_SUCCESS);
}
else
{
jnj_print("look for the error, there is one.");
exit(EXIT_FAILURE);
}
watho[strcspn(watho, "\n")] = '\0';
}
}



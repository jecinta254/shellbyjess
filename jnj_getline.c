#include "shell.h"
/**
 * jnj_getline - Read a line from standard input.
 * @size: The size of the buffer.
 * @watho: Pointer to the buffer where the line will be stored.
 */

void jnj_getline(char *watho, size_t size)
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
perror("Error reading command");
exit(EXIT_FAILURE);
}
}

watho[strcspn(watho, "\n")] = '\0';
}

#include "shell.h"

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

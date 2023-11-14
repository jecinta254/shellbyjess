#include "shell.h"

/**
* jnj_print - it prints a string to standard output.
* @jnjstring: the string to be printed.
*/

void jnj_print(const char *jnjstring)
{
write(STDOUT_FILENO, jnjstring, strlen(jnjstring));
}


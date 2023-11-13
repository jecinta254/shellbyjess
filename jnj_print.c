#include "shell.h"

void jnj_print(const char *jnjstring)
{
        write(STDOUT_FILENO, jnjstring, strlen(jnjstring));
}


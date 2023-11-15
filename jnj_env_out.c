#include "shell.h"

/**
 * jnj_env - prints the current environment variables.
 * this was created by jecinta and joseph.
 */
void jnj_envout(void)
{
    int x = 0;
    while (environ[x] != NULL)

    {
        printf("%s\n", environ[x]);
        x++;
    }
}

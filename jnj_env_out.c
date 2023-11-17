#include "shell.h"

/**
 * run_env - prints the current environment variables.
 */
void run_env(void)
{
    char **env_var = environ;
    while (*env_var != NULL)
    {
        jnj_print(*env_var);
        jnj_print("\n");
        env_var++;
    }
}

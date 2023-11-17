#include "shell.h"
/**
 * run_env - Run the environment command.
 * Returns: 0 on success, -1 on failure.
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


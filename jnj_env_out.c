#include "shell.h"

/**
<<<<<<< HEAD
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
=======
* jnj_envout - prints the current environment variables.
*
* this was created by jecinta and joseph.
*/
void jnj_envout(void)
{
int i = 0;
while (environ[i] != NULL)

{
printf("%s\n", environ[i]);
i++;
}
>>>>>>> f370579e2f12f2686767d18b721fe14323fc4b06
}

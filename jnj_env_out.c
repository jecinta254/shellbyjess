#include "shell.h"

/**
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
}

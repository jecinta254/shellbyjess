#include "shell.h"

/**
* jnj_prompt - it prints the shell prompt.
*/

void jnj_prompt(void)
{
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s$ ", cwd);
    }
    else
    {
        perror("getcwd");
jnj_print("joseph_jecinta_ownshell$ ");
}
}

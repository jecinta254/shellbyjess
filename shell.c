#include "shell.h"

/**
* main - the entry point of the shell program.
* Return: Always 0.
*/

int main(void)
{

char watho[BUFFER_SIZE];
size_t bufsize = BUFFER_SIZE;
char *line = NULL;

if (isatty(fileno(stdin)))
{
while (true)
{
jnj_prompt();
jnj_readcmd(watho, sizeof(watho));

if (strcmp(watho, "exit\n") == 0)
{
	break;
}
            else if (strncmp(watho, "cd", 2) == 0)
            {
                char *path = strtok(watho + 2, " \t\n");
                if (path == NULL)
                    path = getenv("HOME");
                cd_directory(path);
            }
else if (strcmp(watho, "env\n") == 0)
{
jnj_envout();
}

else
{
if (command_exists_path(watho))
{
jnj_execute2(watho);
}
  else
{
jnj_print("Oooops, Check your PATH.\n");
}
}
if (feof(stdin))
{
jnj_print("\n");
break;
}

if (watho[0] != '\0' && watho[0] != '\n')
{
jnj_execute(watho);
}
}
}

else

{
while (fgets(watho, sizeof(watho), stdin) != NULL)
{

watho[strcspn(watho, "\n")] = '\0';

if (watho[0] != '\0')
{
jnj_execute(watho);
}
}
}

return (0);

}

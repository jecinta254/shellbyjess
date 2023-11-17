#include "shell.h"
/**
 * trim_spaces - Trim leading and trailing spaces from a string.
 * @str: The input string
 * Returns: str
 */
char *trim_spaces(char *str)
{
char *end = str + strlen(str) - 1;

while (end > str && isspace((unsigned char)(*end)))
{
end--;
}

*(end + 1) = '\0';

while (*str && isspace((unsigned char)(*str)))
{
str++;
}

return (str);
}
/**
 * execute_logical_commands - Execute logical commands
 * @commands: The array of commands to execute.
 * @count: The number of commands in the array.
 * Returns: The result of logical commands
 */
void execute_logical_commands(char *commands)
{
char *token_and = strtok(commands, "&&");
while (token_and != NULL)
{
char *token_or = strtok(token_and, "||");

while (token_or != NULL)
{
if (token_or[0] != '\0' && token_or[0] != '\n')
{
jnj_execute(trim_spaces(token_or));
}
token_or = strtok(NULL, "||");
}

token_and = strtok(NULL, "&&");
}
}
/**
 * execute_commands - Execute a series of commands.
 * @commands: The array of commands to execute.
 * @count: The number of commands in the array.
 * Returns: The exit status of the last executed command.
 */
void execute_commands(char *commands)
{ 

char *token = strtok(commands, ";");
while (token != NULL)
{
if (token[0] != '\0' && token[0] != '\n')
{
execute_logical_commands(trim_spaces(token));
}
token = strtok(NULL, ";");
}
}


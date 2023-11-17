#include "shell.h"
#include <stdio.h>
/**
 * execute_alias - Execute an alias command.
 * @alias_args: The alias command to execute.
 * This function takes an alias command and executes it.
 * Returns: None.
 */
void execute_alias(const char *alias_args)
{
(void)alias_args;

printf("Executing alias: %s\n", alias_args);
}


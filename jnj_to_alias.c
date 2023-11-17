#include "shell.h"
#include <stdio.h>

void execute_alias(const char *alias_args)
{
(void)alias_args;

printf("Executing alias: %s\n", alias_args);
}


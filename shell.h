#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

extern char **environ;
void execute_logical_commands(char *commands);
void execute_commands(char *commands);
void jnj_prompt(void);
void jnj_print(const char *jnjstring);
void jnj_readcmd(char *watho, size_t size);
void jnj_execute(const char *watho);
void jnj_getline(char *watho, size_t size);
void run_env(void);
void execute_alias(const char *alias_args);

#endif

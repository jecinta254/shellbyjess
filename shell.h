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

#define BUFFER_SIZE 1024

void jnj_prompt(void);
void jnj_print(const char *jnjstring);
void jnj_readcmd(char *watho, size_t size);
void jnj_execute(const char *watho);
int command_exists(const char *command);
void run_env(void);
int our_env(void);
extern char **environ;
void jnj_execute2(const char *watho);
void jnj_envout(void);
int watho_exists(const char *watho);
int jnj_path(void);

#endif

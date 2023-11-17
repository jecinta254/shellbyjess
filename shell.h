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

<<<<<<< HEAD
extern int exit_flag;
extern char **environ;

void execute_logical_commands(char *commands);

void execute_commands(char *commands);
=======
>>>>>>> f370579e2f12f2686767d18b721fe14323fc4b06
void jnj_prompt(void);
void jnj_print(const char *jnjstring);
void jnj_readcmd(char *watho, size_t size);
void jnj_execute(const char *watho);
void jnj_getline(char *watho, size_t size);
void run_env(void);
<<<<<<< HEAD
=======
int our_env(void);
extern char **environ;
void jnj_execute2(const char *watho);
void jnj_envout(void);
int watho_exists(const char *watho);
int jnj_path(void);
void execute_shell(void);
>>>>>>> f370579e2f12f2686767d18b721fe14323fc4b06

#endif


#ifndef BAHARI_HEADER_FILE
#define BAHARI_HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define OUR_WRITE_BUF_SIZE 1024
#define OUR_BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define OUR_HIST_FILE	".simple_shell_history"
#define OUR_HIST_MAX	4096

extern char **environ;

/**
 * struct our_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct our_liststr
{
	int num;
	char *str;
	struct our_liststr *next;
} our_list_t;

/**
 * struct our_passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct
 * @our_arg: a string generated from getline containing arguments
 * @our_argv: an array of strings generated from arg
 * @our_path: a string path for the current command
 * @our_argc: the argument count
 * @line_count: the error count
 * @errorNumber: the error code for exit()s
 * @our_linecount_flag: if on count this line of input
 * @our_fname: the program filename
 * @our_env: linked list local copy of environ
 * @environ: our modified copy of environ from LL env
 * @our_history: the history node
 * @our_alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @our_cmd_buf: address of pointer to cmd_buf, on if chaining
 * @our_cmd_buf_type: CMD_type ||, &&, ;
 * @readFileDescriptor: the fd from which to read line input
 * @our_histcount: the history line number count
 */
typedef struct our_passinfo
{
	char *our_arg;
	char **our_argv;
	char *our_path;
	int our_argc;
	unsigned int line_count;
	int errorNumber;
	int our_linecount_flag;
	char *our_fname;
	our_list_t *our_env;
	our_list_t *our_history;
	our_list_t *our_alias;
	char **environ;
	int env_changed;
	int status;

	/* pointer to cmd ; chain buffer, for memory management */

	char **our_cmd_buf;
	int our_cmd_buf_type; /* CMD_type ||, &&, ; */
	int readFileDescriptor;
	int our_histcount;
} our_info_t;

#define OUR_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct our_builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct our_builtin
{
	char *type;
	int (*func)(our_info_t *);
} our_builtin_table;

/* input_run.c */
int our_hsh(our_info_t *, char **);
int our_find_builtin(our_info_t *);
void our_find_cmd(our_info_t *);
void our_fork_cmd(our_info_t *);

/* __parser.c */
int our_is_cmd(our_info_t *, char *);
char *our_dup_chars(char *, int, int);
char *our_find_path(our_info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* input_run.c */
int our_hsh(our_info_t *, char **);
int our_find_builtin(our_info_t *);
void our_find_cmd(our_info_t *);
void our_fork_cmd(our_info_t *);

/* errors.c */
void _our_eputs(char *);
int _our_eputchar(char);
int _our_putfd(char c, int fd);
int _our_putsfd(char *, int fd);

/* str_token.c */
int our_strlen(char *);
int our_strcmp(char *, char *);
char *our_starts_with(const char *, const char *);
char *our_strcat(char *, char *);

/* str_token1.c */
char *our_strcpy(char *, char *);
char *our_strdup(const char *);
void our_puts(char *);
int our_putchar(char);

/* exit.c */
char *_our_strncpy(char *, char *, int);
char *_our_strncat(char *, char *, int);
char *_our_strchr(char *, char);

/* custom_tokenizer.c */
char **our_strtow(char *, char *);
char **our_strtow2(char *, char);

/* reallocate_mem.c */
char *our_memset(char *, char, unsigned int);
void our_ffree(char **);
void *our_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int our_fpointer(void **);

/* atoi.c */
int ourInteractive(our_info_t *);
int ourDelimiter(char, char *);
int ourAlpha(int);
int stringandInteger(char *);

/* errors1.c */
int _our_erratoi(char *);
void our_print_error(our_info_t *, char *);
int our_print_d(int, int);
char *our_convert_number(long int, int, int);
void our_remove_comments(char *);

/* builtin.c */
int exit_Shell(our_info_t *);
int change_Directory(our_info_t *);
int show_Help(our_info_t *);

/* builtin1.c */
int _our_history(our_info_t *);
int unset_our_alias(our_info_t *, char *);
int set_our_alias(our_info_t *, char *);
int _our_alias(our_info_t *);
int print_our_alias(our_list_t *);

/* get_line.c */
ssize_t our_input_buf(our_info_t *, char **, size_t *);
ssize_t our_get_input(our_info_t *);
ssize_t our_read_buf(our_info_t *, char *, size_t *);
int our_getline(our_info_t *, char **, size_t *);
void our_sigintHandler(__attribute__((unused))int sig_num);

/* getinformation.c */
void our_clear_info(our_info_t *);
void our_set_info(our_info_t *, char **);
void our_free_info(our_info_t *, int);

/* environment.c */
int _our_env(our_info_t *);
char *getEnvironments(our_info_t *, const char *);
int _our_setenv(our_info_t *);
int _our_unsetenv(our_info_t *);
int populate_our_env_list(our_info_t *);


/* custom_get_environment.c */
char **our_get_environ(our_info_t *);
int our_unsetenv(our_info_t *, char *);
int our_setenv(our_info_t *, char *, char *);

/* history.c */
char *our_get_history_file(our_info_t *info);
int our_write_history(our_info_t *info);
int our_read_history(our_info_t *info);
int our_build_history_list(our_info_t *info,
char *our_buf, int linecount);
int our_renumber_history(our_info_t *info);

/* list.c */
our_list_t *our_add_node(our_list_t **, const char *, int);
our_list_t *our_add_node_end(our_list_t **, const char *, int);
size_t our_print_list_str(const our_list_t *);
int our_delete_node_at_index(our_list_t **, unsigned int);
void our_free_list(our_list_t **);

/* list1.c */
size_t our_list_len(const our_list_t *);
char **our_list_to_strings(our_list_t *);
size_t our_print_list(const our_list_t *);
our_list_t *our_node_starts_with(our_list_t *, char *, char);
ssize_t our_get_node_index(our_list_t *, our_list_t *);

/* _variables.c */
int our_is_chain(our_info_t *, char *, size_t *);
void our_check_chain(our_info_t *, char *, size_t *, size_t, size_t);
int our_replace_alias(our_info_t *);
int our_replace_vars(our_info_t *);
int our_replace_string(char **, char *);

#endif

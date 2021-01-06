#ifndef _HOLBERTON_H_
#define _HOLBERTON_H_

/*  space to include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define UNUSED(x) (void)(x)
#define AND_COMP 2
#define OR_COMP  1
#define LAST_COM 0
/*Structure definition*/
/**
 * struct token_search - structure to define the token searcher
 * @symbol: symbol that represents the token
 * @status: status to represent the token action
 * @len: quantity of characters in the token
 *
 * Description: singly linked list node structure for command list
 */
typedef struct token_search
{
	char *symbol;
	int status;
	int len;
} token;

/**
 * struct command_list - singly linked list with commands
 * @command: command to apply
 * @data_len: quantity of arguments
 * @status: status to represent the token action
 * @next: pointer to the next command
 *
 * Description: singly linked list node structure for command list
 */
typedef struct command_list
{
	char **command;
	int data_len;
	struct command_list *next;
	int status;
} c_list;

/**
 * struct creator_params - singly linked list
 * @com_list: actual command being executed
 * @aliases: pointer that store all the shell aliases
 * @line: pointer that stores what the user writes
 * @counter: counter of shell, shows error in the lines
 * @argv: Entry to program arguments
 * @start: Indicates to continue prompt cycle
 * @status: Returns the number of executing code of every process
 *
 * Description: This structure give us input arguments
 * to create processes - for Holberton project
 */
typedef struct creator_params
{
	struct command_list *com_list;
	struct alias *aliases;
	char **line;
	int *counter;
	char **argv;
	char *start;
	int *status;
} creator_args;

/**
 * struct builtin - struct to create function pointers for built in commands
 * @command: string that contains the user command
 * @f: function to execute the user command
 */
typedef struct builtin
{
	char *command;
	int (*f)(creator_args *, char **, int *);
} builtin_t;

/**
 * struct env_data - struct to help with variable expansions
 * @shell_pid: actual pid of shell
 * @last_status: last status returned
 * @word_len: quantity of word to expand
 * @env_len: variable env result
 * @start: beginning of variable expansion
 * @end: end of variable expansion
 */
struct env_data
{
	pid_t shell_pid;
	int last_status;
	int *word_len;
	int *env_len;
	int start;
	int end;
};

/**
 * struct alias - struct to define the alias variables
 * @name: actual name of the alias
 * @value: value of the actual name
 * @next: pointer to the next structure
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_l;

/* Space for function prototypes*/
int _putchar(char c);
int _puts(char *s);
int process_selector(char *filename, char **command, int *status);
void free_grid(char **grid, int height);
char **extract_string(char *string, int *data_length);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
int _strcmp(char *p1, char *p2);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *c_number_to_arr(char *array_data, int n);
unsigned int cal_digits(unsigned int n);
int errno_lin_st(char *name, char *error);
int errno_per(char *name, int line, char *error);
int errno_found(char *name, int line, char *error);
char *path_searcher(char **command, char *env);
char *_getenv(const char *name);
int new_pro(creator_args *param);
int _atoi(char *s);
void handler_ctrlc(int sig);
int isNumber(char *s);
int errno_int(char *name, int line, char *error, char *code);
int handle_error(creator_args *param, char **command, int *data_length);
int str_srch(char *array, char charac);
int (*get_op_func(char *string))(creator_args *, char **, int *);
int _unsetenv(creator_args *param, char **command, int *data_length);
int _setenv(creator_args *param, char **command, int *data_length);
int initialize_env(void);
int _strncmp(char *p1, char *p2, int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
/*space for extern variables*/
extern char **environ;
void free_env(void);
int initialize_env(void);
int print_env(void);
c_list *command_getter(char *string, creator_args *params);
char *command_separator(char *string, int *status);
void free_andnext(creator_args *params);
char *line_parser(creator_args param, char *line);
int alias_logic(creator_args *param, char **command, int *data_length);
void alias_free(creator_args param);
void replace_aliases(creator_args param);
int open_file(creator_args *param, char *argv[]);
int print_allias(creator_args *param, char **command, int *data_length);
char *_getline(const int fd);
int execute_command(creator_args *arg);
void and_logic(creator_args *arg);
void or_logic(creator_args *arg);
int _envset_val(char *name, char *value);
int cd_logic(creator_args *param, char **command, int *data_length);
int errno_cust(char *name, int line, char *error, char *message, int code);
#endif

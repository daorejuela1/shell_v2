#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "../main.h"

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

int print_allias(creator_args *param, char **command, int *data_length);
int _envset_val(char *name, char *value);
int cd_logic(creator_args *arg, char **command, int *data_length);
char *_getenv(const char *name);
char *path_searcher(char **command, char *env);
int _atoi(char *s);
int print_env(void);
void handler_ctrlc(int sig __attribute__((unused)));
void alias_free(creator_args param);
int print_allias(creator_args *param, char **command, int *data_length);
void replace_aliases(creator_args param);
int isNumber(char *s);
int handle_error(creator_args *arg, char **command, int *data_length);
int (*get_op_func(char *string))(creator_args *, char **, int *);
int _unsetenv(creator_args *param, char **command, int *data_length);
int _setenv(creator_args *param, char **command, int *data_length);
int initialize_env(void);
void free_env(void);
int alias_logic(creator_args *param, char **command, int *data_length);
int help_logic(creator_args *param, char **command, int *data_length);
#endif

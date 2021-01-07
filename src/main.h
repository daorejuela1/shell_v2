#ifndef _MAIN_H_
#define _MAIN_H_

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
#define DRIGTH_REDIR 4
#define RIGTH_REDIR 3
#define AND_COMP 2
#define OR_COMP  1
#define LAST_COM 0

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

/*space for extern variables*/
extern char **environ;
#endif

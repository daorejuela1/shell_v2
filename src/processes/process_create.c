#include "processes.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../operators/operators.h"
#include "../messages/messages.h"
#include "../builtins/builtins.h"
/**
 *new_pro - executes the shell main logic checking
 *if a file is worth
 *@arg: structure with all arguments
 *Return: modified path or null if failed
 */
int new_pro(creator_args *arg)
{
	*(arg->line) = line_parser(*arg, *(arg->line));
	arg->com_list = command_getter(*(arg->line), arg);
	while (arg->com_list)
	{
		switch (arg->com_list->status)
		{
		case LAST_COM:
			execute_command(arg);
		break;
		case AND_COMP:
			and_logic(arg);
			break;
		case OR_COMP:
			or_logic(arg);
			break;
		}
	}
	return (*(arg->status));
}

/**
 * execute_command - search in the path and executes desired command
 * @arg: structure with all the arguments
 *
 * Return: status of the executed command
 */
int execute_command(creator_args *arg)
{
	int data_length = 0;
	char **command = NULL, *en_variable = NULL, *full_path = NULL;
	int (*built_infunc)(creator_args *, char **, int *);
	struct stat st;

	replace_aliases(*arg), command = arg->com_list->command;
	data_length = arg->com_list->data_len;
	if (command[0] != NULL)
	{
		built_infunc = get_op_func(command[0]);
		if (built_infunc != NULL)
			return (built_infunc(arg, command, &data_length));
		en_variable = _getenv("PATH");
		if (stat(command[0], &st) == 0
				&& access(command[0], X_OK) == 0 &&
				(en_variable || str_srch(command[0], '/') != -1))
			process_selector(command[0], command, arg->status);
		else if (stat(command[0], &st) == 0 && access(command[0], X_OK) != 0)
			*(arg->status) = errno_per(arg->argv[0], *(arg->counter), command[0]);
		else
		{
			full_path = path_searcher(command, en_variable);
			if (full_path == NULL)
				*(arg->status) = errno_found(arg->argv[0], *(arg->counter), command[0]);
			else if (stat(full_path, &st) == 0 && access(full_path, X_OK) != 0)
				*(arg->status) = errno_per(arg->argv[0], *(arg->counter), command[0]);
			else if (stat(full_path, &st) == 0 && access(full_path, X_OK) == 0)
				process_selector(full_path, command, arg->status);
		}
		free(en_variable), en_variable = NULL, free(full_path);
		free_andnext(arg);
	}
	else
		free_andnext(arg);
	return (*(arg->status));
}

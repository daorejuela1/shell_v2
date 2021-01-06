#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"

/**
 * alias_free - frees the alias strings inside param
 * @param: structure that contains the aliases
 *
 * Returns: Nothing
 */
void alias_free(creator_args param)
{
	alias_l *temp = NULL;

	while (param.aliases)
	{
		temp = param.aliases->next;
		free(param.aliases->name);
		free(param.aliases->value);
		free(param.aliases);
		param.aliases = temp;
	}
}
/**
 * print_allias - prints the linked list containing the alias information
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
int print_allias(creator_args *param, char **command, int *data_length)
{
	alias_l *temp = NULL;

	UNUSED(command);
	UNUSED(data_length);
	temp = param->aliases;
	if (*data_length == 1)
	{
		while (temp)
		{
			printf("%s='%s'\n", temp->name, temp->value);
			temp = temp->next;
		}
	}
	return (0);
}


/**
 * replace_aliases - replace the command with the corresponding alias if found
 * @param: structure that contains the aliases
 *
 * Returns: Nothing
 */
void replace_aliases(creator_args param)
{
	alias_l *temp = NULL;
	char *new_string = NULL;
	int repeat = 0;

	do {
	temp = param.aliases;
	repeat = 0;
	while (temp)
	{
		if (_strcmp(temp->name, param.com_list->command[0]) == 0)
		{
			free(param.com_list->command[0]);
			new_string = _calloc(_strlen(temp->value) + 1, 1);
			_strncpy(new_string, temp->value, _strlen(temp->value));
			param.com_list->command[0] = new_string;
			repeat = 1;
		}
		temp = temp->next;
	}
	} while (repeat == 1);
}

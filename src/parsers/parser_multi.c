#include "parsers.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"

static int command_end;
static token tokens[] = {
		{"&&", AND_COMP, 2},
		{"||", OR_COMP, 2},
		{">>", DRIGTH_REDIR, 2},
		{">", RIGTH_REDIR, 1},
		{"<", LEFT_REDIR, 1},
		{";", LAST_COM, 1},
	};
/**
 *command_separator - gets the commands to do separed by ;
 *@string: Input line from the user
 *@status: Node operation
 *Return: Always double pointer with commands
 */
static char *command_separator(char *string, int *status)
{
	char *line = NULL;
	int i = 0, j = 0, word_len = 0, offset = 1, end_here = 0;

	if (!string)
		return (NULL);
	word_len = _strlen(string);
	for (i = command_end; i < word_len; i++)
	{
		end_here = 0;
		for (j = 0; j < 6; j++)
		{
			if (tokens[j].len == 2 && string[i] == *tokens[j].symbol)
			{
				if (i != word_len - 1 && string[i + 1] == *(tokens[j].symbol + 1))
				{
					end_here = 1, *status = tokens[j].status, offset = tokens[j].len;
					break;
				}
			}
			else if (tokens[j].len == 1 && string[i] == *tokens[j].symbol)
			{
				end_here = 1, *status = tokens[j].status, offset = tokens[j].len;
				break;
			}
		}
		if (end_here)
			break;
	}
	if (i == command_end)
		return (NULL);
	line = _calloc(i - command_end + 1, 1);
	if (!line)
		return (NULL);
	line = _strncpy(line, string + command_end, i - command_end);
	command_end = i + offset;
	return (line);
}

/**
 *command_getter - gets the commands to do separed by ;
 *@string: Input line from the user
 *@params: structure with command information
 *Return: Always double pointer with commands
 */
c_list *command_getter(char *string, creator_args *params)
{
	c_list *new_command = NULL, *initial = NULL;
	char *line = NULL;
	int counter = 0, data_len = 0, status = 0;

	command_end = 0;
	while ((line = command_separator(string, &status)))
	{
		free(line);
		new_command = malloc(sizeof(c_list));
		new_command->next = NULL;
		if (!new_command)
			return (NULL);
		counter++;
		if (counter == 1)
		{
			params->com_list = new_command;
			initial = params->com_list;
		}
		else
		{
			params->com_list->next = new_command;
			params->com_list = params->com_list->next;
		}
	}
	command_end = 0;
	params->com_list = initial;
	while ((line = command_separator(string, &status)))
	{
		data_len = 0;
		params->com_list->command = extract_string(line, &data_len);
		(params->com_list)->data_len = data_len;
		(params->com_list)->status = status;
		free(line);
		params->com_list = params->com_list->next;
	}
	return (initial);
}

/**
 *free_andnext - frees the linked list and past to next command;
 *@params: Structure with the command to clean
 *Return: Nothing
 */
void free_andnext(creator_args *params)
{
	c_list *temp = NULL;

	free_grid((params->com_list)->command, params->com_list->data_len);
	temp = params->com_list->next;
	free(params->com_list);
	params->com_list = temp;
}

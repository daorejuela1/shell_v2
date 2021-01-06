#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
/**
* isNumber - checks if string is just numbers
* @s: pointer to a string of error messages
* Return: error code 127
*/
int isNumber(char *s)
{
	int i;

	for (i = 0; s[i] != 0; i++)
	{
		if ((s[i] < '0' || s[i] > '9'))
			return (0);
	}
	return (1);
}

/**
* handle_error - handle exit behavior and error output
* @arg: structure with the run state
* @command: user input
* @data_length: command length
* Return: error code 2 or previous if no new error
*/
int handle_error(creator_args *arg, char **command, int *data_length)
{
	int state = 0;

	if (command[1] != NULL)
	{
		if (isNumber(command[1]))
		{
			*(arg->status) = _atoi(command[1]);
			*(arg->start) = 0;
			free_andnext(arg);
			*data_length = 0;
			return (*(arg->status));
		}
		else
		{
			state = errno_int(arg->argv[0], *(arg->counter), command[0], command[1]);
			*(arg->status) = state;
			free_andnext(arg);
			*data_length = 0;
			return (state);
		}
	}
	*(arg->start) = 0;
	free_andnext(arg);
	*data_length = 0;
	return (*(arg->status));
}

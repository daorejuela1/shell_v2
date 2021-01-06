#include "operators.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
#include "../processes/processes.h"

/**
 * and_logic - logic to be used when having two commands joined by &&
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void and_logic(creator_args *arg)
{
	int status = 0;
		status = execute_command(arg);
	if (status != 0)
	{
		while (arg->com_list && arg->com_list->status == AND_COMP)
			free_andnext(arg);
		if (arg->com_list)
			free_andnext(arg);
	}
}

/**
 * or_logic - logic to be used when having two commands joined by &&
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void or_logic(creator_args *arg)
{
	int status = 0;

	status = execute_command(arg);
	if (status == 0)
	{
		while (arg->com_list && arg->com_list->status == OR_COMP)
			free_andnext(arg);
		if (arg->com_list)
			free_andnext(arg);
	}
}

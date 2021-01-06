#include "files.h"
#include "../builtins/builtins.h"
#include "../getline/_getline.h"
#include "../messages/messages.h"
#include "../utils/utils.h"
#include "../processes/processes.h"

/**
 * open_file - reads commands from an input file
 * @arg: structure that contains the aliases
 * @argv: arguments taken as input for the program
 *
 * Return: Nothing
 */
int open_file(creator_args *arg, char *argv[])
{
	int fd = 0;
	char *line = NULL;

	arg->line = &line;
	fd = open(argv[1], 0);
	if (fd == -1)
		return (errno_lin_st(argv[0], argv[1]));
	while ((line = _getline(fd)))
	{
	arg->counter++; /*non interactive mode*/
	*arg->status = (_strcmp(line, "env\n") == 0) ? print_env() : new_pro(arg);
	free(line);
	}
	close(fd);
	return (*arg->status);
}

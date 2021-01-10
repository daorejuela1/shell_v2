#include "files.h"
#include "../builtins/builtins.h"
#include "../getline/_getline.h"
#include "../messages/messages.h"
#include "../utils/utils.h"
#include "../processes/processes.h"

/**
 * startup_file - reads commands from the home file in $HOME .hshrc
 * @arg: structure that contains the aliases
 *
 * Return: Nothing
 */
int startup_file(creator_args *arg)
{
	int fd = 0;
	char *line = NULL, *home = NULL;

	home = _getenv("HOME");
	if (home)
	{
		home = _realloc(home, _strlen(home), _strlen(home) + 9);
		_strcat(home, "/.hshrc");
	}
	else
		return (0);
	arg->line = &line;
	fd = open(home, 0);
	free(home);
	if (fd == -1)
		return (0);
	while ((line = _getline(fd)))
	{
	*arg->counter = *arg->counter + 1; /*non interactive mode*/
	*arg->status = (_strcmp(line, "env\n") == 0) ? print_env() : new_pro(arg);
	free(line);
	}
	close(fd);
	return (*arg->status);
}

/**
 * open_file - reads commands from an input file
 * @arg: structure that contains the aliases
 * @file_toopen: name of the file thats needed to be opened
 *
 * Return: Nothing
 */
int open_file(creator_args *arg, char *file_toopen)
{
	int fd = 0;
	char *line = NULL;

	arg->line = &line;
	fd = open(file_toopen, 0);
	if (fd == -1)
		return (errno_lin_st(arg->argv[0], file_toopen));
	while ((line = _getline(fd)))
	{
	*arg->counter = *arg->counter + 1; /*non interactive mode*/
	*arg->status = (_strcmp(line, "env\n") == 0) ? print_env() : new_pro(arg);
	free(line);
	}
	close(fd);
	return (*arg->status);
}

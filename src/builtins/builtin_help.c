#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../getline/_getline.h"
#define ERR_ME ("%s: %d: %s: Not found\n")
/**
 * print_help - prints the linked list containing the alias information
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
static int print_help(creator_args *param, char *command, int *data_length)
{
	char *base_path = "doc/";
	char *line = NULL, *path = NULL;
	int fd = 0;

	UNUSED(command);
	UNUSED(data_length);
	path = _calloc(_strlen(base_path) + _strlen(command) + 1, 1);
	_strncpy(path, base_path, _strlen(base_path));
	_strcat(path, command);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
	{
		perror("File");
		fprintf(stderr, ERR_ME, param->argv[0], *param->counter, command);
		return (2);
	}
	while ((line = _getline(fd)))
	{
		write(STDOUT_FILENO, line, _strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
	return (0);
}

/**
 * help_logic - selector to know what help should print
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
int help_logic(creator_args *param, char **command, int *data_length)
{
	if (*data_length == 1)
		print_help(param, "help", data_length);
	else
	{
		print_help(param, command[1], data_length);
	}
	free_andnext(param);
	return (0);
}

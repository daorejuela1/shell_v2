#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../getline/_getline.h"
#define CURRENT_HISTORY (history[i % HISTORY_BUFFER])

static char *history[HISTORY_BUFFER];

/**
 * print_history - prints the list containing the array information
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
int print_history(creator_args *param, char **command, int *data_length)
{
	int line = 0;

	UNUSED(data_length);
	UNUSED(command);
	for (line = 0; line < *param->counter; line++)
	{
		if (line >= HISTORY_BUFFER)
			break;
		printf("%d %s", line, history[line]);
	}
	free_andnext(param);
	return (0);
}

/**
 * save_history - saves the current line in history memory
 * @param: structure with the used variables
 * @line: array of array with the input commands
 *
 * Return: 0 on success and -1 in any error case
 */
int save_history(creator_args param, char *line)
{
	char *history_line = NULL;

	history_line = _calloc(_strlen(line) + 1, 1);
	if (!history_line)
		return (-1);
	_strncpy(history_line, line, _strlen(line));
	history[(*param.counter - 1) % HISTORY_BUFFER] = history_line;
	return (0);
}

/**
 * init_history - initialize history memory
 * @arg: structure with the used variables
 *
 * Return: 0 on success and -1 in any error case
 */
int init_history(creator_args *arg)
{
	int fd = 0, i = 0;
	char *line = NULL, *home = NULL;

	for (i = 0; i < HISTORY_BUFFER; i++)
		history[i] = NULL;
	home = _getenv("HOME");
	if (home)
	{
		home = _realloc(home, _strlen(home), _strlen(home) + 14);
		_strcat(home, "/.hsh_history");
	}
	else
		return (0);
	fd = open(home, 0);
	free(home);
	if (fd == -1)
		return (0);
	while ((line = _getline(fd)))
	{
		line = _realloc(line, _strlen(line), _strlen(line) + 3);
		line[_strlen(line)] = '\n';
		line[_strlen(line) + 1] = 0;
		history[*arg->counter % HISTORY_BUFFER] = line;
		*arg->counter = *arg->counter + 1;
	}
	close(fd);
	return (0);
}

/**
 * export_history - export history memory to file .hsh_history
 * @arg: structure with the used variables
 *
 * Return: 0 on success and -1 in any error case
 */
int export_history(creator_args arg)
{
	int fd = 0, i = 0;
	char *home = NULL;

	home = _getenv("HOME");
	UNUSED(arg);
	if (home)
	{
		home = _realloc(home, _strlen(home), _strlen(home) + 14);
		_strcat(home, "/.hsh_history");
	}
	else
	{
	for (i = 0; i < HISTORY_BUFFER; i++)
		if (history[i % HISTORY_BUFFER])
			free(history[i % HISTORY_BUFFER]);
		return (0);
	}
	fd = open(home, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	free(home);
	if (fd == -1)
	{
		perror("Error: ");
		return (0);
	}
	for (i = 0; i < HISTORY_BUFFER; i++)
	{
	if (history[i % HISTORY_BUFFER])
	{
	write(fd, CURRENT_HISTORY, _strlen(CURRENT_HISTORY));
	free(history[i % HISTORY_BUFFER]);
	}
	}
	close(fd);
	return (0);
}

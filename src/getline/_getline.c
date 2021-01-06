#include "_getline.h"
#include "holberton.h"
#define OLD_SIZE (((READ_SIZE + 1) * repetitions) + 1)
#define NEW_SIZE (((READ_SIZE + 1) * (repetitions + 1)) + 1)
static int repetitions;
static char *output;
/**
 * _getline - Gets a line from an input
 * @fd: file descriptor number
 *
 * Return: pointer to the memory
 */
char *_getline(const int fd)
{
	int readed = 0, index = 0;
	char buffer[READ_SIZE + 1], *line = NULL, *temp = NULL;

	do {
		readed = read(fd, &buffer, READ_SIZE);
		if (readed == -1)
			return (NULL);
		if (readed)
		{
			temp = _realloc(output, OLD_SIZE, NEW_SIZE);
			if (temp == NULL)
				return (NULL);
			output = temp;
			buffer[readed] = 0;
			_strcat(output, buffer);
			repetitions++;
		}
		index = getindex(output, 10);
	} while (readed == READ_SIZE && index == -1);
	if (index != -1 && output)
	{
		return (split_line(index));
	}
	if (output)
	{
		line = _calloc(NEW_SIZE, 1);
		if (line == NULL)
			return (NULL);
		_strncpy(line, output, _strlen(output));
		free(output);
		output = NULL;
		repetitions = 0;
		return (line);
	}
	return (NULL);
}
/**
 * getindex - search for a character inside an array
 * @array: array to search the character from
 * @chr: character to search for
 *
 * Return: index of the chr in array or -1 if not found
 */
int getindex(char *array, char chr)
{
	int index = 0;

	if (!array)
		return (-1);
	for (index = 0; *(array + index); index++)
	{
		if (array[index] == chr)
			return (index);
	}
	return (-1);
}

/**
 *split_line - split line until new line character is found
 *@index: index of current solution
 *
 *Return: String used by split line
 *
 */
char *split_line(int index)
{
	char *line = NULL, *temp = NULL;

	line = _calloc(index + 1, 1);
	if (line == NULL)
		return (NULL);
	_strncpy(line, output, index);
	line[index] = 0;
	if (*(output + index + 1) == 0)
	{
		free(output);
		output = NULL;
		repetitions = 0;
	}
	else
	{
		temp = _calloc(NEW_SIZE, 1);
		_strncpy(temp, output + index + 1, _strlen(output + index + 1));
		free(output);
		output = temp;
	}
	return (line);
}

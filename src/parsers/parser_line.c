#include "parsers.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
#include "../builtins/builtins.h"

/**
 * remove_comments - removes the comments in the line by detecting # char
 * @line: string that contains comments
 *
 * Return: line of null if error
 */
static char *remove_comments(char *line)
{
	int i = 0, line_len = 0, flag = 0, comment = 0;
	char *new_line = NULL;

	line_len = _strlen(line);
	for (i = 0; i < line_len; i++)
	{
		if (line[i] == *"#")
			comment = 1;
		if (line[i] == *" ")
			flag = 1;
		else if ((line[i] == *"#" && i == 0) || (line[i] == *"#" && flag))
			break;
		if (line[i] != *" ")
			flag = 0;
	}
	if (!comment)
		return (line);
	if (!i)
	{
		free(line);
		return (NULL);
	}
	new_line = _calloc(i + 1, 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	_strncpy(new_line, line, i);
	free(line);
	return (new_line);
}

/**
 * get_value - gets the value of the desired input
 * @param: pid of the shell
 * @line: status request
 * @data: struct with temp data
 *
 * Return: Pointer to the created value
 */
static char *get_value(creator_args param, char *line, struct env_data data)
{
	char *new_word = NULL, *new_env = NULL;
	pid_t num_digits = 0;

	if (!data.shell_pid && !data.last_status)
	{
		data.end--;
		new_word = _calloc(data.end - data.start + 1, 1);
		if (!new_word)
			return (NULL);
		_strncpy(new_word, line + data.start + 1, data.end - data.start);
		*data.word_len = _strlen(new_word);
		new_env = _getenv(new_word);
		if (!new_env)
			*data.env_len = 0;
		else
			*data.env_len = _strlen(new_env);
		free(new_word);
	}
	else
	{
	num_digits = data.shell_pid | *(param.status);
	while (num_digits != 0)
	{
		num_digits = num_digits / 10;
		(*data.env_len)++;
	}
	(*data.env_len)++;
	new_env = _calloc(*data.env_len + 1, 1);
	if (!new_env)
		return (NULL);
	c_number_to_arr(new_env, data.shell_pid | *(param.status));
	}
	return (new_env);
}

/**
 *expand_variables - expand variables starting with $ included $? and $$
 *@param: structure with all params
 *@line: input with variables to be expanded
 *
 * Return: string with lines expanded
 */
static char *expand_variables(creator_args param, char *line)
{
	struct env_data data;
	int line_len = 0, i = 0, env_len = 0, word_len = 0, last_len = 0;
	char *new_line = NULL, *new_env = NULL;

	data.start = -1, data.end = -1, data.word_len = &word_len;
	data.env_len = &env_len, data.last_status = 0, data.shell_pid = 0;
	line_len = _strlen(line);
	for (i = 0; i < line_len; i++)
	{
		if (i != line_len - 1 && line[i] == *"$" && line[i + 1] == *" ")
			break;
		if (i != line_len - 1 && line[i] == *"$" && line[i + 1] == *"$")
		{
			data.start = i, data.end = i + 3, data.shell_pid = getpid();
			break;
		}
		if (i != line_len - 1 && line[i] == *"$" && line[i + 1] == *"?")
		{
			data.start = i, data.end = i + 3, data.last_status = 1;
			break;
		}
		if (line[i] == *"$")
			data.start = i;
		if (data.start >= 0 && (line[i] == *" " || line[i] == *"\n"))
		{
			data.end = i;
			break;
		}
	}
	if ((data.start == -1 && data.end == -1) || data.end == data.start)
		return (line);
	new_env = get_value(param, line, data), last_len = line_len - data.end;
	new_line = _calloc(line_len - word_len + env_len + 1, 1);
	_strncpy(new_line, line, data.start);
	if (new_env)
		_strcat(new_line, new_env), free(new_env);
	if (data.end != line_len)
		_strncpy(new_line + data.start + env_len, line + data.end, last_len);
	free(line);
	return (new_line);
}

/**
 * line_parser - removes comments and interpretate line content
 * @param: structure with all parameters
 * @line: raw input line
 *
 * Return: None if error ocurs, Parsed line otherwise
 */
char *line_parser(creator_args param, char *line)
{
	line = remove_comments(line);
	if (line)
		line = expand_variables(param, line);
	return (line);
}

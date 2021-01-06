#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
/**
 *_getenv - gets actual enviroment
 *@name: key of enviroment
 *Return: string with paths of environment
 */
char *_getenv(const char *name)
{
	char *key = NULL, *copy = NULL;
	char *result = NULL;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		copy = _calloc(_strlen(environ[i]) + 1, 1);
		if (copy == NULL)
			return (NULL);
		_strncpy(copy, environ[i], _strlen(environ[i]));
		key = strtok(copy, "=");
		if (_strcmp((char *)name, key) == 0)
		{
			key = strtok(NULL, "=");
			if (key == NULL)
				key = "";
			result = _calloc(_strlen(key) + 1, 1);
			if (result == NULL)
				return (NULL);
			_strncpy(result, key, _strlen(key));
			free(copy);
			copy = NULL;
			return (result);
		}
		free(copy);
		copy = NULL;
	}
	free(copy);
	copy = NULL;
	return (NULL);
}
/**
 *path_searcher - search through path for a valid file
 *@command: argument to check if exist or not
 *@env: actual environment
 *Return: modified path or null if failed
 */
char *path_searcher(char **command, char *env)
{
	char *token = NULL, *copy;
	char *final_path = NULL;
	struct stat st;

	if (env == NULL)
		return (NULL);
	copy = _calloc(_strlen(env) + 1, 1);
	_strncpy(copy, env, _strlen(env));
	token = strtok(copy, ":");
	while (token != NULL)
	{
		final_path = _calloc(_strlen(token) + _strlen(command[0]) + 2, 1);
		_strncpy(final_path, token, _strlen(token));
		_strcat(final_path, "/");
		_strcat(final_path, command[0]);
		if (stat(final_path, &st) == 0)
		{
			free(copy);
			return (final_path);
		}
		token = strtok(NULL, ":");
		free(final_path);
	}
	free(copy);
	return (NULL);
}

/**
 *_atoi - function to transform from array to integer
 *@s: input string
 *
 *Return: 0 if not number, or first number found in the string.
 */
int _atoi(char *s)
{
	int tamano = 0, i, sign = 1;
	unsigned int number = 0;

	for (tamano = 0; s[tamano] != 0; tamano++)
	{
		if (s[tamano] == '-')
			sign = sign * -1;
		else if (s[tamano] >= 48 && s[tamano] <= 57)
			break;
	}
	for (i = 0; s[i] != 0; i++)
	{
		if (s[i] >= 48 && s[i] <= 48 + 9)
		{
			number = number * 10 + s[i] - '0';
		}
		else if (number != 0)
		{
			break;
		}
	}
	return (sign * number);
}

/**
*print_env - prints the environ variable
*Return: Always 0
*/
int print_env(void)
{
	int i = 0;

	while (environ && environ[i] != NULL)
	{
		_puts(environ[i]);
		_puts("\n");
		i++;
	}
	return (0);
}

/**
*handler_ctrlc - redirects ctrl c to add new line
*@sig: signal handled
*Return: Nothing
*/
void handler_ctrlc(int sig __attribute__((unused)))
{
	_puts("\n$ ");
}

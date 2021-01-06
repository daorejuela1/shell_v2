#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
/**
 * _unsetenv - deletes a variable from the path if exist
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
int _unsetenv(creator_args *param, char **command, int *data_length)
{
	char **new_environ = NULL, *name = NULL;
	size_t len;
	int i = 0, j = 0, env_vars;

	UNUSED(data_length);
	name = command[1];
	if (name == NULL || name[0] == '\0' || str_srch(name, '=') != -1)
	{
		free_andnext(param);
		return (-1);
	}
	if (!environ)
		return (0);
	len = _strlen(name);
	for (env_vars = 0; environ[env_vars]; env_vars++)
		;
	new_environ = _calloc((env_vars) + 1, sizeof(environ));
	if (!new_environ)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, len) == 0 && (environ[i])[len] == '=')
		{
			free(environ[i]);
			environ[i] = NULL;
		}
		else
		{
			new_environ[j] = environ[i];
			j++;
		}
	}
	free(environ);
	environ = new_environ;
	environ[j] = 0;
	free_andnext(param);
	return (0);
}

/**
 * _setenv - overwrites or create a new variable with the value
 * @param: structure with the used variables
 * @command: array of array with the input commands
 * @data_length: quantity of commands
 *
 * Return: 0 if succes or -1 if error found
 */
int _setenv(creator_args *param, char **command, int *data_length)
{
	char *new_word, **new_environ, *name = NULL, *value = NULL;
	int env_vars = 0, len = 0;

	UNUSED(data_length), UNUSED(param), name = command[1];
	if (name == NULL || name[0] == '\0' || str_srch(name, '=') != -1)
	{
		free_andnext(param);
		return (-1);
	}
	value = command[2];
	if (!value)
	{
		free_andnext(param);
		return (-1);
	}
	len = _strlen(name);
	new_word = _calloc(_strlen(name) + _strlen(value) + 2, 1);
	_strncpy(new_word, name, _strlen(name));
	_strcat(new_word, "="), _strcat(new_word, value);
	for (env_vars = 0; environ[env_vars]; env_vars++)
	{
		if (_strncmp(environ[env_vars], name, len) == 0 &&
				(environ[env_vars])[len] == '=')
		{
			free(environ[env_vars]);
			environ[env_vars] = new_word;
			free_andnext(param);
			return (0);
		}
	}
	new_environ = _realloc(environ, (env_vars + 1) * sizeof(environ),
			(env_vars + 2) * sizeof(environ));
	if (!new_environ)
		return (-1);
	new_environ[env_vars] = new_word;
	new_environ[env_vars + 1] = 0;
	environ = new_environ;
	free_andnext(param);
	return (0);
}

/**
 * initialize_env - converts all env variables to malloc
 *
 * Return: -1 if malloc error 0 if ok
 */
int initialize_env(void)
{
	char **new_environ;
	int env_vars = 0;

	for (env_vars = 0; environ[env_vars]; env_vars++)
		;
	new_environ = malloc((env_vars + 1) * sizeof(environ));
	if (!new_environ)
	{
		return (-1);
	}
	for (env_vars = 0; environ[env_vars]; env_vars++)
	{
		new_environ[env_vars] = _calloc(_strlen(environ[env_vars]) + 1, 1);
		if (!new_environ[env_vars])
		{
			return (-1);
		}
		_strncpy(new_environ[env_vars], environ[env_vars],
				_strlen(environ[env_vars]));
	}
	new_environ[env_vars] = 0;
	environ = new_environ;
	return (0);
}

/**
 * free_env - frees the list at the end
 */
void free_env(void)
{
	int env_vars = 0;

	for (env_vars = 0; environ[env_vars]; env_vars++)
	{
		free(environ[env_vars]);
		environ[env_vars] = NULL;
	}
	free(environ);
}

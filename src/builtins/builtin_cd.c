#include "builtins.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
/**
 * change_dir - change current directory to path & and set env variables
 * @arg: structure with all the arguments
 * @path: path to directory to change
 *
 * Return: Nothing
 */
static int change_dir(creator_args *arg, char *path)
{
	char old_pwd[512];
	struct stat st;
	int line = 0;

	line = *(arg->counter);
	if (stat(path, &st) == 0 && access(path, X_OK) == 0)
	{
		getcwd(old_pwd, 512);
		chdir(path);
		_envset_val("PWD", path);
		_envset_val("OLDPWD", old_pwd);
	}
	else if (stat(path, &st) == 0 && access(path, X_OK) != 0)
	{
		return (errno_per("cd", line, path));
	}
	else
	{
		return (errno_cust(arg->argv[0], line, path, "cd: can't cd to ", 0));
	}
	return (0);
}

/**
 * _envset_val - overwrites or create a new variable with the value
 * @name: name of the environment variable
 * @value: value of the environment variable
 *
 * Return: 0 if succes or -1 if error found
 */
int _envset_val(char *name, char *value)
{
	int len = 0, env_vars = 0;
	char *new_word = NULL, **new_environ = NULL;

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
	return (0);
}


/**
 * cd_logic - selector to know if alias should be printed or stored
 * @arg: structure with all the arguments
 * @command: array of array with the input commands
 * @data_length: quantity of commands as input
 *
 * Return: 0 on success and -1 in any error case
 */
int cd_logic(creator_args *arg, char **command, int *data_length)
{
	int status = 0;
	char *home_directory = NULL, *old_pwd = NULL;

	if (*data_length == 1 || *command[1] == '~')
	{
		home_directory = _getenv("HOME");
		if (!home_directory)
			status = 0;
		else
		{
			status = (change_dir(arg, home_directory));
			free(home_directory);
		}
	}
	else if (*command[1] == '-')
	{
		old_pwd = _getenv("OLDPWD");
		if (!old_pwd)
			old_pwd = _getenv("PWD");
		write(STDOUT_FILENO, old_pwd, _strlen(old_pwd));
		write(STDOUT_FILENO, "\n", 1);
		status = change_dir(arg, old_pwd);
		free(old_pwd);
	}
	else
	{
		status = change_dir(arg, command[1]);
	}
	free_andnext(arg);
	return (status);
}

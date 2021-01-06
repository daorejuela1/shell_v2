#include "messages.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
/**
 * errno_lin_st - Search and show error messages
 * @error: The pointer to error message
 * @name: The string of err_message
 * Return: Nothing
 */
int errno_lin_st(char *name, char *error)
{
	char *err_message;
	int data_len = 0;
	char *message = ": 0: Can't open ";

	data_len = _strlen(name) + _strlen(error) + _strlen(message);
	err_message = _calloc(data_len + 2, 1);
	if (err_message == NULL)
		return (-1);
	_strncpy(err_message, name, _strlen(name));
	_strcat(err_message, message);
	_strcat(err_message, error);
	_strcat(err_message, "\n");
	write(STDERR_FILENO, err_message, _strlen(err_message));
	free(err_message);
	return (127);
}

/**
 * errno_per - Counts the line numbers
 * @name: The name of shell or sh
 * @line: The number of lines
 * @error: The pointer to error messages
 * Return: status code 126
 */
int errno_per(char *name, int line, char *error)
{
	char *err_message, *storage_array;
	int data_len = 0, num_digits = 0, position = 0;
	char *message = ": Permission denied\n";

	num_digits = line;
	while (num_digits != 0)
	{
		num_digits = num_digits / 10;
		position++;
	}
	data_len = _strlen(name) + _strlen(error) + _strlen(message);
	err_message = _calloc(data_len + 5 + position, 1);
	if (err_message == NULL)
		return (0);
	storage_array = _calloc(position + 1, 1);
	if (storage_array == NULL)
		return (0);
	_strncpy(err_message, name, _strlen(name));
	_strcat(err_message, ": ");
	_strcat(err_message, c_number_to_arr(storage_array, line));
	_strcat(err_message, ": ");
	_strcat(err_message, error);
	_strcat(err_message, message);
	write(STDERR_FILENO, err_message, _strlen(err_message));
	free(err_message);
	free(storage_array);
	return (126);
}

/**
 * errno_found - Prints error depending on the case
 * @name: The pointer to a string of error messages
 * @line: The number of lines
 * @error: The pointer to error
 * Return: Error code 127
 */
int errno_found(char *name, int line, char *error)
{
	char *err_message, *storage_array;
	int data_len = 0, num_digits = 0, position = 0;
	char *message = ": not found\n";

	num_digits = line;
	while (num_digits != 0)
	{
		num_digits = num_digits / 10;
		position++;
	}
	data_len = _strlen(name) + _strlen(error) + _strlen(message);
	err_message = _calloc(data_len + 5 + position, 1);
	if (err_message == NULL)
		return (0);
	storage_array = _calloc(position + 1, 1);
	if (storage_array == NULL)
		return (0);
	_strncpy(err_message, name, _strlen(name));
	_strcat(err_message, ": ");
	_strcat(err_message, c_number_to_arr(storage_array, line));
	_strcat(err_message, ": ");
	_strcat(err_message, error);
	_strcat(err_message, message);
	write(STDERR_FILENO, err_message, _strlen(err_message));
	free(err_message);
	free(storage_array);
	return (127);
}

/**
 * errno_int - Prints error depending on the case
 * @name: The pointer to a string of error messages
 * @line: The number of lines
 * @error: The pointer to error
 * @code: The code that rise the error
 * Return: Error code 2
 */
int errno_int(char *name, int line, char *error, char *code)
{
	char *err_message, *storage_array;
	int data_len = 0, num_digits = 0, position = 0;
	char *message = ": Illegal number: ";

	num_digits = line;
	while (num_digits != 0)
	{
		num_digits = num_digits / 10;
		position++;
	}
	data_len = _strlen(name) + _strlen(error) + _strlen(message);
	err_message = _calloc(data_len + 6 + position + _strlen(code), 1);
	if (err_message == NULL)
		return (0);
	storage_array = _calloc(position + 1, 1);
	if (storage_array == NULL)
		return (0);
	_strncpy(err_message, name, _strlen(name));
	_strcat(err_message, ": ");
	_strcat(err_message, c_number_to_arr(storage_array, line));
	_strcat(err_message, ": ");
	_strcat(err_message, error);
	_strcat(err_message, message);
	_strcat(err_message, code);
	_strcat(err_message, "\n");
	write(STDERR_FILENO, err_message, _strlen(err_message));
	free(err_message);
	free(storage_array);
	return (2);
}

/**
 * errno_cust - Counts the line numbers
 * @name: The name of shell or sh
 * @line: The number of lines
 * @error: The pointer to error messages
 * @message: custom message to represent
 * @code: custom code to return
 * Return: status code 126
 */
int errno_cust(char *name, int line, char *error, char *message, int code)
{
	char *err_message, *storage_array;
	int data_len = 0, num_digits = 0, position = 0;

	num_digits = line;
	while (num_digits != 0)
	{
		num_digits = num_digits / 10;
		position++;
	}
	data_len = _strlen(name) + _strlen(error) + _strlen(message);
	err_message = _calloc(data_len + 6 + position, 1);
	if (err_message == NULL)
		return (0);
	storage_array = _calloc(position + 1, 1);
	if (storage_array == NULL)
		return (0);
	_strncpy(err_message, name, _strlen(name));
	_strcat(err_message, ": ");
	_strcat(err_message, c_number_to_arr(storage_array, line));
	_strcat(err_message, ": ");
	_strcat(err_message, message);
	_strcat(err_message, error);
	_strcat(err_message, "\n");
	write(STDERR_FILENO, err_message, _strlen(err_message));
	free(err_message);
	free(storage_array);
	return (code);
}

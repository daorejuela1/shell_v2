#include "operators.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
#include "../processes/processes.h"
#include "../getline/_getline.h"
#define WRITE_CREATE (O_WRONLY | O_CREAT | O_TRUNC)
#define READ (O_RDONLY)
#define WRITE_APPEND (O_WRONLY | O_CREAT | O_APPEND)
#define NORMAL_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)
#define FILENAME (file_pointer->command[0])
#define DELIMETER (delimeter->command[0])
#define SYNTAX_ERROR "%s: %d: Syntax error: newline unexpected\n"
#define CREATE_ERROR "%s: %d: cannot create %s"
#define OPEN_ERROR "%s: %d: cannot open %s"
#define NEXT_EXIST (file_pointer->next != NULL)
#define NEXTDEL_EXIST (delimeter->next != NULL)
/**
 * right_redir - logic to be used when having one redirection >
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void right_redir(creator_args *arg)
{
	c_list *file_pointer = NULL;
	int fd = 0, std_outcpy = 0, quantity = 0, i = 0;
	char message[1024];

	file_pointer = arg->com_list;
	while (file_pointer && file_pointer->status == RIGTH_REDIR && NEXT_EXIST)
	{
		quantity++;
		file_pointer = file_pointer->next;
	}
	if (!file_pointer || !file_pointer->command || !file_pointer->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter + 1);
		for (i = 0; i <= quantity; i++)
			free_andnext(arg);
		*arg->status = 2;
		return;
	}
	file_pointer = arg->com_list->next;
	for (i = 0; i < quantity; i++)
	{
		fd = open(file_pointer->command[0], WRITE_CREATE, NORMAL_MODE);
		if (fd == -1)
		{
			sprintf(message, CREATE_ERROR, arg->argv[0], *arg->counter, FILENAME);
			perror(message);
			for (i = 0; i <= quantity; i++)
				free_andnext(arg);
			*arg->status = 2;
			return;
		}
		file_pointer = file_pointer->next;
	}
	std_outcpy = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execute_command(arg);
	for (i = 0; i < quantity; i++)
		free_andnext(arg);
	dup2(std_outcpy, STDOUT_FILENO);
	close(fd);
}

/**
 * dright_redir - logic to be used when having double redirection >>
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void dright_redir(creator_args *arg)
{
	c_list *file_pointer = NULL;
	int fd = 0, std_outcpy = 0, quantity = 0, i = 0;
	char message[1024];

	file_pointer = arg->com_list;
	while (file_pointer && file_pointer->status == DRIGTH_REDIR && NEXT_EXIST)
	{
		quantity++;
		file_pointer = file_pointer->next;
	}
	if (!file_pointer || !file_pointer->command || !file_pointer->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter + 1);
		for (i = 0; i <= quantity; i++)
			free_andnext(arg);
		*arg->status = 2;
		return;
	}
	file_pointer = arg->com_list->next;
	for (i = 0; i < quantity; i++)
	{
		fd = open(file_pointer->command[0], WRITE_APPEND, NORMAL_MODE);
		if (fd == -1)
		{
			sprintf(message, CREATE_ERROR, arg->argv[0], *arg->counter, FILENAME);
			perror(message);
			for (i = 0; i <= quantity; i++)
				free_andnext(arg);
			*arg->status = 2;
			return;
		}
		file_pointer = file_pointer->next;
	}
	std_outcpy = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execute_command(arg);
	for (i = 0; i < quantity; i++)
		free_andnext(arg);
	dup2(std_outcpy, STDOUT_FILENO);
	close(fd);
}

/**
 * left_redir - logic to be used when having one input redirection <
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void left_redir(creator_args *arg)
{
	c_list *file_pointer = NULL;
	int fd = 0, stdin_cpy = 0, quantity = 0, i = 0;
	char message[1024];
	struct stat st;

	file_pointer = arg->com_list;
	while (file_pointer && file_pointer->status == LEFT_REDIR && NEXT_EXIST)
		quantity++, file_pointer = file_pointer->next;
	if (!file_pointer || !file_pointer->command || !file_pointer->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter + 1);
		for (i = 0; i <= quantity; i++)
			free_andnext(arg);
		*arg->status = 2;
		return;
	}
	file_pointer = arg->com_list->next;
	for (i = 0; i < quantity; i++)
	{
		fd = open(file_pointer->command[0], READ, NORMAL_MODE);
		if (fd == -1)
		{
			sprintf(message, OPEN_ERROR, arg->argv[0], *arg->counter, FILENAME);
			if (stat(file_pointer->command[0], &st) != 0)
				fprintf(stderr, "%s: %s\n", message, "No such file");
			else
				perror(message);
			for (i = 0; i <= quantity; i++)
				free_andnext(arg);
			*arg->status = 2;
			return;
		}
		file_pointer = file_pointer->next;
	}
	stdin_cpy = dup(STDIN_FILENO), dup2(fd, STDIN_FILENO);
	execute_command(arg);
	for (i = 0; i < quantity; i++)
		free_andnext(arg);
	dup2(stdin_cpy, STDIN_FILENO), close(fd);
}
/**
 * heredoc - logic to be used when having dounle input redirection <<
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void heredoc(creator_args *arg)
{
	c_list *delimeter = NULL;
	int fd = 0, read = 0, stdin_cpy = 0, quantity = 0, i = 0;
	char *temp_file = "/tmp/shell_v2heredoc_daor1475", *line = NULL;
	size_t len = 0;

	delimeter = arg->com_list;
	while (delimeter && delimeter->status == HEREDOC && NEXTDEL_EXIST)
		quantity++, delimeter = delimeter->next;
	if (!delimeter || !delimeter->command || !delimeter->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter + 1);
		for (i = 0; i <= quantity; i++)
			free_andnext(arg);
		*arg->status = 2;
		return;
	}
	delimeter = arg->com_list->next;
	fd = open(temp_file, WRITE_CREATE, NORMAL_MODE);
	while (1) /*interactive mode*/
	{
		if (isatty(STDIN_FILENO))
			_puts("> ");
		read = getline(&line, &len, stdin);
		if (read == EOF)
		{
			if (isatty(STDIN_FILENO))
				_puts("\n");
			break;
		}
		if (_strncmp(line, DELIMETER, _strlen(DELIMETER)) == 0)
			break;
		write(fd, line, _strlen(line));
	}
	fflush(stdin), free(line), close(fd);
	fd = open(temp_file, READ);
	stdin_cpy = dup(STDIN_FILENO), dup2(fd, STDIN_FILENO);
	execute_command(arg);
	for (i = 0; i < quantity; i++)
		free_andnext(arg);
	dup2(stdin_cpy, STDIN_FILENO), close(fd);
}

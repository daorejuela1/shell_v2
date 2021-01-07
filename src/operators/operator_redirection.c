#include "operators.h"
#include "../utils/utils.h"
#include "../parsers/parsers.h"
#include "../messages/messages.h"
#include "../processes/processes.h"
#define WRITE_CREATE (O_WRONLY | O_CREAT | O_TRUNC)
#define NORMAL_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)
#define FILENAME (file_pointer->command[0])
#define SYNTAX_ERROR "%s: %d: Syntax error: newline unexpected\n"
#define CREATE_ERROR "%s: %d: cannot create %s"
#define NEXT_EXIST (file_pointer->next != NULL)
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

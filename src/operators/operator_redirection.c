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
/**
 * right_redir - logic to be used when having one redirection >
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void right_redir(creator_args *arg)
{
	c_list *file_pointer = NULL;
	int fd = 0, dup_state = 0, std_outcpy = 0;
	char message[1024];

	file_pointer = arg->com_list->next;
	if (!file_pointer || !file_pointer->command || !file_pointer->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter);
		free_andnext(arg);
		free_andnext(arg);
		return;
	}
	fd = open(file_pointer->command[0], WRITE_CREATE, NORMAL_MODE);
	if (fd == -1)
	{
		sprintf(message, CREATE_ERROR, arg->argv[0], *arg->counter, FILENAME);
		perror(message);
		free_andnext(arg);
		free_andnext(arg);
		return;
	}
	std_outcpy = dup(STDOUT_FILENO);
	dup_state = dup2(fd, STDOUT_FILENO);
	if (dup_state == -1)
	{
		sprintf(message, CREATE_ERROR, arg->argv[0], *arg->counter, FILENAME);
		perror(message);
		close(fd);
		free_andnext(arg);
		free_andnext(arg);
		return;
	}
	execute_command(arg);
	free_andnext(arg);
	dup_state = dup2(std_outcpy, STDOUT_FILENO);
	close(fd);
}

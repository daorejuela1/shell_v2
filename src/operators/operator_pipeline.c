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
#define NEXTPIPE_EXIST (delimeter->next != NULL)

/**
 * mid_pipeline - logic to be used when being in the middle of pipelines |
 * @i: number of the pipeline
 * @pipe_pid: pipe used to communicate data
 * @arg: structure with current command
 *
 * Returns: Nothing
 */
static void mid_pipeline(int i, int pipe_pid[2][2], creator_args *arg)
{
	int stdout_cpy = 0, stdin_cpy = 0;

	stdin_cpy = dup(STDIN_FILENO);
	dup2(pipe_pid[(i + 1) % 2][READ_END], STDIN_FILENO);
	close(pipe_pid[(i + 1) % 2][READ_END]);
	stdout_cpy = dup(STDOUT_FILENO);
	pipe(pipe_pid[(i) % 2]);
	dup2(pipe_pid[(i) % 2][WRITE_END], STDOUT_FILENO);
	close(pipe_pid[(i) % 2][WRITE_END]);
	execute_command(arg);
	dup2(stdout_cpy, STDOUT_FILENO);
	dup2(stdin_cpy, STDIN_FILENO);
}


/**
 * pipeline - logic to be used when having dounle input redirection <<
 * @arg: structure that contains all the data
 *
 * Returns: Nothing
 */
void pipeline(creator_args *arg)
{
	c_list *delimeter = NULL;
	int stdout_cpy = 0, quantity = 0, i = 0, stdin_cpy = 0;
	int pipe_pid[2][2];

	delimeter = arg->com_list;
	while (delimeter && delimeter->status == PIPELINE && NEXTPIPE_EXIST)
		quantity++, delimeter = delimeter->next;
	delimeter = arg->com_list;
	if (!delimeter || !delimeter->command || !delimeter->command[0])
	{
		fprintf(stderr, SYNTAX_ERROR, arg->argv[0], *arg->counter + 1);
		for (i = 0; i <= quantity; i++)
			free_andnext(arg);
		*arg->status = 2;
		return;
	}
	for (i = 0; i <= quantity; i++)
	{
		if (i == 0)
		{
		pipe(pipe_pid[0]);
		stdout_cpy = dup(STDOUT_FILENO);
		dup2(pipe_pid[0][WRITE_END], STDOUT_FILENO);
		close(pipe_pid[0][WRITE_END]);
		execute_command(arg);
		dup2(stdout_cpy, STDOUT_FILENO);
		}
		else if (i != quantity)
		{
		mid_pipeline(i, pipe_pid, arg);
		}
		else
		{
		stdin_cpy = dup(STDIN_FILENO);
		dup2(pipe_pid[(i + 1) % 2][READ_END], STDIN_FILENO);
		close(pipe_pid[(i + 1) % 2][READ_END]);
		execute_command(arg);
		dup2(stdin_cpy, STDIN_FILENO);
		}
	}
	}

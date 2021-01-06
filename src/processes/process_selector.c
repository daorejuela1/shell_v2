#include "processes.h"
#define CHILDSTATUS(x)	(x >> 8)
/**
 * process_selector - function that selects the children processes
 * @filename: executable name of file
 * @command: buffer variable where data is stored temporarily
 * @status: returns children running status
 * Return: Always 0 on success
*/

int process_selector(char *filename, char **command, int *status)
{
	pid_t children;

	children = fork();
	if (children < 0) /*Error*/
	{
		perror("Error: Children process can't be created");
		exit(1);
	}
	if (children == 0) /*Children process*/
	{
		if (execve(filename, command, environ) == -1)
		{
			exit(2);
		}
	}
	if (children > 0) /*current process*/
	{
		wait(status);
		*status = CHILDSTATUS(*status);
	}
return (0);
}

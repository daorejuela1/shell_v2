#ifndef _PARSER_H_
#define _PARSER_H_

#include "../main.h"

/*Structure definition*/

/**
 * struct env_data - struct to help with variable expansions
 * @shell_pid: actual pid of shell
 * @last_status: last status returned
 * @word_len: quantity of word to expand
 * @env_len: variable env result
 * @start: beginning of variable expansion
 * @end: end of variable expansion
 */
struct env_data
{
	pid_t shell_pid;
	int last_status;
	int *word_len;
	int *env_len;
	int start;
	int end;
};

/**
 * struct token_search - structure to define the token searcher
 * @symbol: symbol that represents the token
 * @status: status to represent the token action
 * @len: quantity of characters in the token
 *
 * Description: singly linked list node structure for command list
 */
typedef struct token_search
{
	char *symbol;
	int status;
	int len;
} token;

char *line_parser(creator_args param, char *line);
c_list *command_getter(char *string, creator_args *params);
void free_andnext(creator_args *params);
#endif

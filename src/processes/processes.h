#ifndef _PROCESESS_H_
#define _PROCESESS_H_

#include "../main.h"

int new_pro(creator_args *arg);
int execute_command(creator_args *arg);
int process_selector(char *filename, char **command, int *status);
#endif

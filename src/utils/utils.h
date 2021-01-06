#ifndef _UTILS_H_
#define _UTILS_H_

#include "../main.h"
/*  space to include libraries */

void free_grid(char **grid, int height);
char **extract_string(char *string, int *data_length);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
unsigned int cal_digits(unsigned int n);
int _putchar(char c);
int _puts(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *c_number_to_arr(char *array_data, int n);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *p1, char *p2);
int str_srch(char *array, char charac);
int _strncmp(char *p1, char *p2, int n);
#endif

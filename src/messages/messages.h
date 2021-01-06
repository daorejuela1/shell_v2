#ifndef _HOLBERTON_H_
#define _HOLBERTON_H_
int errno_lin_st(char *name, char *error);
int errno_per(char *name, int line, char *error);
int errno_found(char *name, int line, char *error);
int errno_int(char *name, int line, char *error, char *code);
int errno_cust(char *name, int line, char *error, char *message, int code);
#endif

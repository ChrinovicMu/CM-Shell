#ifndef SHELL_BUILTINS_H
#define SHELL_BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int shell_help(char **args);
int shell_cd(char **args);
int shell_create_dir(char **args);
int shell_exit(char **args); 

extern int (*builtin_func[])(char **);
extern char *builtin_str[];

int builtin_num(void);


#endif // SHELL_BUILTINS_H

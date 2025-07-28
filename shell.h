#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int handle_builtin(char **args);

#endif /* SHELL_H */

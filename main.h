#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct token_s - linked list
 * @token: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */

typedef struct token_s
{
	char *token;
	unsigned int len;
	struct token_s *next;
} token_t;

char *Read_line(ssize_t *exit);
token_t *tokenicer(char *line, char *delimit);
token_t *add_node_end(token_t **head, const char *str);
void free_list(token_t *head);
token_t *_getenv(char *str);
token_t *_stat_checker(token_t *head, token_t *path);
char **_list_to_array(token_t *head);
int _EXE_Cute(char **args);
void _env(void);
char *_concat(char *str, char *add);

#endif

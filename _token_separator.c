
#include "main.h"

/**
 * tokenicer - separate strings with a delimitter
 * @line: string to tokeniz
 * @delimit: string used like a delimitter
 * Return: a linked list with values of string tokenized
 */

token_t *tokenicer(char *line, char *delimit)
{
	char *list = NULL;
	token_t *tokens;

	tokens = NULL;
	list = strtok(line, delimit);
	while (list != NULL)
	{
		add_node_end(&tokens, list);
		list = strtok(NULL, delimit);
	}
	return (tokens);
}

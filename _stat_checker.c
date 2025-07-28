#include "main.h"

/**
 * _stat_checker - pruves a command on different paths
 * @head: linked list with command and arguments
 * @path: a tring with the path route
 * Return: a valid string with the full path to execute
*/

token_t *_stat_checker(token_t *head, token_t *path)
{
	token_t *temp;
	struct stat *buff;
	char *new_str = NULL, *compare_str = NULL;

	buff = malloc(sizeof(struct stat));
	temp = path;
	if (stat(head->token, buff) == 0)
	{
		free_list(path);
		free(buff);
		return (head);
	}
	while (temp)
	{
		new_str = _concat(temp->token, "/");
		compare_str = _concat(new_str, head->token);
		if (stat(compare_str, buff) == 0)
		{
			free(head->token);
			head->token = strdup(compare_str);
			free_list(path);
			free(compare_str);
			free(new_str);
			free(buff);
			return (head);
		}
		free(compare_str);
		free(new_str);
		temp = temp->next;
	}
	free(buff);
	free_list(head);
	free_list(path);
	return (NULL);
}

/**
 * _concat - concatenates two string
 * @str: the first part of the string
 * @add: the last part of the string
 * Return: Returns a new string with the necesary ammount of memory
*/

char *_concat(char *str, char *add)
{
	char *new = NULL;
	int count = 0, counter = 0;

	new = malloc(strlen(str) + strlen(add) * sizeof(char) + 1);
	if (!new)
		return (NULL);

	while (str[count])
	{
		new[count] = str[count];
		count++;
	}
	while (add[counter])
	{
		new[count] = add[counter];
		count++;
		counter++;
	}
	new[count] = '\0';
	return (new);
}

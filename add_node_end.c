#include "main.h"

/**
 * add_node_end - adds a node to the end of the linkedlist
 * @head: the first node
 * @str: string to put in the new node
 * Return: returns pointer to the first node
 */

token_t *add_node_end(token_t **head, const char *str)
{
	token_t *temp;
	token_t *loop;
	unsigned int len;

	temp = malloc(sizeof(token_t));
	if (!temp)
	{
		return (NULL);
	}

	len = strlen(str);
	temp->token = strdup(str);
	temp->len = len;
	temp->next = NULL;
	if (*head == NULL)
	{
		*head = temp;
	}
	else
	{
		loop = *head;
		while (loop != NULL)
		{
			if (loop->next == NULL)
			{
				loop->next = temp;
				break;
			}
			loop = loop->next;
		}
	}
	return (*head);
}

#include "main.h"

/**
 * free_list - frees a linked list
 * @head: input linked list
 * Return: Nothing
 */

void free_list(token_t *head)
{
	token_t *temp;

	if (head == NULL)
		return;
	temp = head;
	while (head != NULL)
	{
		head = head->next;
		free(temp->token);
		free(temp);
		temp = head;
	}
	free(head);
}

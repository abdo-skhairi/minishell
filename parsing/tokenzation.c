#include "main.h"

t_token *new_token(char *value, int has_space_after)
{
	t_token *node = malloc(sizeof(t_token));
	if (!node)
		return NULL;
	node->value = value;
	node->has_space_after = has_space_after;
	node->next = NULL;
	return node;
}

void append_token(t_token **head, t_token *new_node)
{
	if (!*head)
	{
		*head = new_node;
		return;
	}
	t_token *tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

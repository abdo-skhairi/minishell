#include "main.h"

void	assign_token_types(t_token *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->value, "|") == 0)
			tokens->type = PIPE;
		else if (ft_strcmp(tokens->value, "<") == 0)
			tokens->type = RED_IN;
		else if (ft_strcmp(tokens->value, ">") == 0)
			tokens->type = RED_OUT;
		else if (ft_strcmp(tokens->value, "<<") == 0)
			tokens->type = HEREDOC;
		else if (ft_strcmp(tokens->value, ">>") == 0)
			tokens->type = APPEND;
		else
			tokens->type = WORD;
		tokens = tokens->next;
	}
}

#include "main.h"

static int count_args(t_token *tokens)
{
	int count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return count;
}

static char **get_command_args(t_token **tokens)
{
	int args_count = count_args(*tokens);
	char **args = malloc(sizeof(char *) * (args_count + 1));
	if (!args)
		return NULL;

	int i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			args[i++] = (*tokens)->value;
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type == RED_IN || (*tokens)->type == RED_OUT
			|| (*tokens)->type == HEREDOC || (*tokens)->type == RED_APPEND)
		{
			*tokens = (*tokens)->next;
			if (*tokens)
				*tokens = (*tokens)->next;
		}
		else
			*tokens = (*tokens)->next;
	}
	args[i] = NULL;
	return args;
}

static t_redirection *get_redirections(t_token **tokens)
{
	t_redirection *head = NULL;
	t_redirection *last = NULL;
	t_token *tmp = *tokens;

	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN || tmp->type == RED_OUT || tmp->type == HEREDOC || tmp->type == RED_APPEND)
		{
			t_token *red_token = tmp;
			t_token *file_token = tmp->next;
			if (!file_token)
				break;

			t_redirection *new_red = malloc(sizeof(t_redirection));
			if (!new_red)
				return NULL;

			if (red_token->type == RED_IN)
				new_red->type = INPUT;
			else if (red_token->type == RED_OUT)
				new_red->type = OUTPUT;
			else if (red_token->type == HEREDOC)
				new_red->type = RED_HEREDOC;
			else
				new_red->type = RED_APPEND;

			new_red->name = file_token->value;
			new_red->next_red = NULL;

			if (!head)
				head = new_red;
			else
				last->next_red = new_red;
			last = new_red;

			tmp = file_token->next;
		}
		else
			tmp = tmp->next;
	}
	return head;
}

t_command *extract_all_commands(t_token *tokens)
{
	t_command *head = NULL;
	t_command *last = NULL;
	while (tokens)
	{
		t_command *new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
			return NULL;
		new_cmd->command = NULL;
		new_cmd->red = NULL;
		new_cmd->next_command = NULL;
		t_token *scan = tokens;
		new_cmd->command = get_command_args(&tokens);
		new_cmd->red = get_redirections(&scan);
		if (!head)
			head = new_cmd;
		else
			last->next_command = new_cmd;
		last = new_cmd;

		while (tokens && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return head;
}

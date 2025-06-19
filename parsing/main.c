#include "main.h"

int get_token_end(char *s, int i)
{
    if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '"'))
    {
        char quote = s[i + 1];
        i += 2;
        while (s[i] && s[i] != quote)
            i++;
        if (s[i] == quote)
            i++;
        return i;
    }
    if (s[i] == '<' || s[i] == '>')
    {
        if (s[i + 1] == s[i])
            return i + 2;
        return i + 1;
    }
    if(s[i] == '|')
        return i + 1;
    if (s[i] == '"' || s[i] == '\'')
    {
        char quote = s[i++];
        while (s[i] && s[i] != quote)
            i++;
        if (s[i] == quote)
            i++;
        return i;
    }
    while (s[i] && !ft_isspace(s[i]) && s[i] != '"' && s[i] != '\'' &&
        s[i] != '<' && s[i] != '>' && s[i] != '|')
        i++;
    return i;
}

int parser(char *s, int *exit_value, t_env *env_list)
{
	t_token *tokens = NULL;
	int i = 0;

	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break;
		int start = i;
		int end = get_token_end(s, i);
		int len = end - start;
		char *val = ft_substr(s, start, len);
		if (!val)
			return -1;
		i = end;
		int has_space = ft_isspace(s[i]);
		append_token(&tokens, new_token(val, has_space));
	}
    assign_token_types(tokens);
    expand_tokens(&tokens, exit_value, env_list);
    join_tokens_with_no_space(&tokens);
    t_command *cmds = extract_all_commands(tokens);
    print_commands(cmds);
	return 0;
}

void minishell(int *exit_value, t_env *env_list)
{
    char *input;
    char *line;
    int eror;

    while (1)
    {
        eror = 0;
        input = readline("s_bash$ ");
        if (!input)
            break;
        add_history(input);
        if(check_syntax_errors_raw(input) == -1)
        {
            *exit_value = 258;
            eror = 1;
        }
        if(eror == 0)
            line = add_spaces_around_symbols(input);
        if (eror == 0)
        {
            parser(line, exit_value, env_list);
            *exit_value = 0;
        }
        free(input);
    }
}

t_env *init_env(char **envp)
{
    t_env *head = NULL;
    while (*envp)
    {
        char *entry = *envp;
        char *equal = ft_strchr(entry, '=');
        if (equal)
        {
            t_env *new = malloc(sizeof(t_env));
            new->key = ft_substr(entry, 0, equal - entry);
            new->value = ft_strdup(equal + 1);
            new->next = head;
            head = new;
        }
        envp++;
    }
    return head;
}

int main(int ac, char **av, char **envp)
{
    int exit;
    t_env *env_list = init_env(envp);

    (void)ac;
    (void)av;
    exit = 0;
    // ft_signals();
    minishell(&exit, env_list);
    return 0;
}

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

int parser(char *s)
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
    expand_tokens(&tokens);
    join_tokens_with_no_space(&tokens);
    assign_token_types(tokens);
    t_command *cmds = extract_all_commands(tokens);
    print_commands(cmds);
	return 0;
}

int main()
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
            eror = 1;
        if(eror == 0)
            line = add_spaces_around_symbols(input);
        if (eror == 0)
            parser(line);
        free(input);
    }
    return 0;
}

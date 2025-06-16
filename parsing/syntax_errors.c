#include "main.h"

int check_unmatched_quotes(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
        {
            char quote = s[i++];
            while (s[i] && s[i] != quote)
                i++;
            if (!s[i])
                return 1;
            i++;
        }
        else
            i++;
    }
    return 0;
}

int check_pipe_errors(char *s)
{
    int i = 0;
    while (s[i] && ft_isspace(s[i]))
        i++;
    if (s[i] == '|')
        return 1;

    while (s[i])
    {
        if (s[i] == '|')
        {
            int j = i + 1;
            while (s[j] && ft_isspace(s[j]))
                j++;
            if (s[j] == '|' || s[j] == '\0')
                return 1;
            if (s[j] == '>' || s[j] == '<')
                return 1;
        }
        i++;
    }
    return 0;
}

int check_invalid_redirections(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '<' || s[i] == '>')
        {
            if ((s[i] == '<' && s[i + 1] == '>') || (s[i] == '>' && s[i + 1] == '<'))
                return 1;
            if (s[i + 1] == '|')
                return 1;
            if ((s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>') ||
                (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<'))
                return 1;
            if (s[i + 1] == s[i])
                i += 2;
            else
                i++;
            while (s[i] && ft_isspace(s[i]))
                i++;
            if (s[i] == '\0' || s[i] == '|' || s[i] == '<' || s[i] == '>')
                return 1;
            continue;
        }
        i++;
    }
    return 0;
}

int check_syntax_errors_raw(char *input)
{
    if (check_unmatched_quotes(input))
    {
        printf("syntax error: unmatched quote\n");
        return -1;
    }
    if (check_invalid_redirections(input))
    {
        printf("syntax error near redirection\n");
        return -1;
    }
    if (check_pipe_errors(input))
    {
        printf("syntax error near unexpected pipe\n");
        return -1;
    }
    return 0;
}

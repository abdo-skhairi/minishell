#include "main.h"

char *my_strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int is_operator(char *str)
{
	if (!str)
		return 0;
	if (ft_strcmp(str, "|") == 0)
		return 1;
	if (ft_strcmp(str, ">") == 0)
		return 1;
	if (ft_strcmp(str, "<") == 0)
		return 1;
	return 0;
}

char *remove_quotes(const char *str)
{
	int len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') ||
	                 (str[0] == '\'' && str[len - 1] == '\'')))
	{
		char *unquoted = malloc(len - 1);
		if (!unquoted)
			return NULL;
		int i = 0;
		while (i < len - 2)
		{
			unquoted[i] = str[i + 1];
			i++;
		}
		unquoted[i] = '\0';
		if (is_operator(unquoted))
		{
			free(unquoted);
			unquoted = malloc(len + 1);
			if (!unquoted)
				return NULL;
			i = 0;
			while (i < len)
			{
				unquoted[i] = str[i];
				i++;
			}
			unquoted[i] = '\0';
		}
		return unquoted;
	}
	char *dup = malloc(len + 1);
	if (!dup)
		return NULL;
	int i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return dup;
}

void join_tokens_with_no_space(t_token **tokens)
{
	t_token *curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->has_space_after == 0)
		{
			char *val1 = remove_quotes(curr->value);
			char *val2 = remove_quotes(curr->next->value);
			char *joined = malloc(ft_strlen(val1) + ft_strlen(val2) + 1);
			if (!joined)
			{
				free(val1);
				free(val2);
				return;
			}
			my_strcpy(joined, val1);
			my_strcat(joined, val2);
			free(curr->value);
			curr->value = joined;
			t_token *tmp = curr->next;
			curr->has_space_after = tmp->has_space_after;
			curr->next = tmp->next;
			free(tmp->value);
			free(tmp);
			free(val1);
			free(val2);
			continue;
		}
		curr = curr->next;
	}
	curr = *tokens;
	while (curr)
	{
		char *unquoted = remove_quotes(curr->value);
		free(curr->value);
		curr->value = unquoted;
		curr = curr->next;
	}
}

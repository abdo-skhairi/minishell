#include "main.h"

int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int is_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int should_add_space_before(char *str, int pos)
{
	return (pos > 0 && str[pos - 1] != ' ');
}

int should_add_space_after(char c)
{
	return (c != '\0' && c != ' ');
}

char *add_spaces_around_symbols(char *input)
{
	int in_quote = 0;
	char quote_char = 0;
	int len = ft_strlen(input);
	char *new_str = malloc(len * 3 + 1);
	if (!new_str)
		return NULL;
	int i = 0, j = 0;
	while (input[i])
	{
		if (!in_quote && is_quote(input[i]))
		{
			in_quote = 1;
			quote_char = input[i];
			new_str[j++] = input[i++];
		}
		else if (in_quote && input[i] == quote_char)
		{
			in_quote = 0;
			new_str[j++] = input[i++];
		}
		else if (!in_quote && is_symbol(input[i]))
		{
			if (should_add_space_before(new_str, j))
				new_str[j++] = ' ';
			new_str[j++] = input[i];
			if ((input[i] == '<' || input[i] == '>') && input[i] == input[i + 1])
				new_str[j++] = input[i++];
			i++;
			if (should_add_space_after(input[i]))
				new_str[j++] = ' ';
		}
		else
			new_str[j++] = input[i++];
	}
	new_str[j] = '\0';
	return new_str;
}

#include "main.h"

int is_quoted(const char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') ||
						 (str[0] == '"' && str[len - 1] == '"')));
}

int is_single_quoted(const char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}

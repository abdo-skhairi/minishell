#include "main.h"

char *my_strcat(char *dest, const char *src)
{
	size_t i = 0;
	size_t j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return dest;
}

char *get_env_value(const char *key)
{
	char *val;

	val = getenv(key);
	if (val)
		return val;
	else
		return "";
}

char *expand_var(const char *src)
{
	char *result = malloc(1);
	if (!result)
		return NULL;
	result[0] = '\0';
	int i = 0;

	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			if (src[i] == '\0')
			{
				size_t len = ft_strlen(result);
				char *tmp = realloc(result, len + 2);
				if (!tmp)
				{
					free(result);
					return NULL;
				}
				result = tmp;
				result[len] = '$';
				result[len + 1] = '\0';
				break;
			}
			else if (src[i] == '$')
			{
				char pid_str[21];
				int pid = getpid();
				int j = 19;
				pid_str[20] = '\0';
				if (pid == 0)
					pid_str[j--] = '0';
				while (pid > 0 && j >= 0)
				{
					pid_str[j--] = (pid % 10) + '0';
					pid /= 10;
				}
				char *pid_val = &pid_str[j + 1];
				char *tmp = realloc(result, ft_strlen(result) + ft_strlen(pid_val) + 1);
				if (!tmp)
				{
					free(result);
					return NULL;
				}
				result = tmp;
				my_strcat(result, pid_val);
				i++;
			}
			else if (src[i] == '?')
			{
				char *tmp = realloc(result, ft_strlen(result) + 2);
				if (!tmp)
				{
					free(result);
					return NULL;
				}
				result = tmp;
				my_strcat(result, "0");
				i++;
			}
			else if (!((src[i] >= 'a' && src[i] <= 'z') ||
					   (src[i] >= 'A' && src[i] <= 'Z') ||
					   (src[i] >= '0' && src[i] <= '9') ||
					   src[i] == '_'))
			{
				size_t len = ft_strlen(result);
				char *tmp = realloc(result, len + 2);
				if (!tmp)
				{
					free(result);
					return NULL;
				}
				result = tmp;
				result[len] = '$';
				result[len + 1] = '\0';
			}
			else
			{
				int start = i;
				while ((src[i] >= 'a' && src[i] <= 'z') ||
					   (src[i] >= 'A' && src[i] <= 'Z') ||
					   (src[i] >= '0' && src[i] <= '9') ||
					   src[i] == '_')
					i++;
				int key_len = i - start;
				char *key = malloc(key_len + 1);
				if (!key)
				{
					free(result);
					return NULL;
				}
				for (int j = 0; j < key_len; j++)
					key[j] = src[start + j];
				key[key_len] = '\0';
				char *val = get_env_value(key);
				char *tmp = realloc(result, ft_strlen(result) + ft_strlen(val) + 1);
				if (!tmp)
				{
					free(key);
					free(result);
					return NULL;
				}
				result = tmp;
				my_strcat(result, val);
				free(key);
			}
		}
		else
		{
			size_t len = ft_strlen(result);
			char *tmp = realloc(result, len + 2);
			if (!tmp)
			{
				free(result);
				return NULL;
			}
			result = tmp;
			result[len] = src[i];
			result[len + 1] = '\0';
			i++;
		}
	}
	return result;
}

char *handle_dollar_quote(const char *str)
{
	if (str[0] == '$' && (str[1] == '\'' || str[1] == '"'))
	{
		char quote = str[1];
		int i = 2;
		int len = 0;
		while (str[i + len] && str[i + len] != quote)
			len++;
		char *res = malloc(len + 1);
		if (!res)
			return NULL;
		for (int j = 0; j < len; j++)
			res[j] = str[i + j];
		res[len] = '\0';
		return res;
	}
	return NULL;
}

void expand_tokens(t_token **tokens)
{
	t_token *curr = *tokens;
	while (curr)
	{
		if (!is_single_quoted(curr->value))
		{
			char *tmp = handle_dollar_quote(curr->value);
			if (tmp)
			{
				free(curr->value);
				curr->value = tmp;
			}
			else
			{
				char *expanded = expand_var(curr->value);
				free(curr->value);
				curr->value = expanded;
			}
		}
		curr = curr->next;
	}
}

#include "main.h"
#include <stdlib.h>
#include <string.h>

char *ft_get_env(t_env *env, const char *key)
{
	while (env)
	{
		if (!strcmp(env->key, key))
			return env->value;
		env = env->next;
	}
	return "";
}

char *expand_var(const char *src, int *exit_value, t_env *env)
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
				size_t len = strlen(result);
				char *tmp = ft_realloc(result, len + 2);
				if (!tmp)
					return free(result), NULL;
				result = tmp;
				result[len] = '$';
				result[len + 1] = '\0';
				break;
			}
			else if (src[i] == '?')
			{
				char *status = ft_itoa(*exit_value);
				if (!status)
					return free(result), NULL;
				char *tmp = ft_realloc(result, strlen(result) + strlen(status) + 1);
				if (!tmp)
					return free(status), free(result), NULL;
				result = tmp;
				strcat(result, status);
				free(status);
				i++;
			}
			else if (!((src[i] >= 'a' && src[i] <= 'z') ||
					   (src[i] >= 'A' && src[i] <= 'Z') ||
					   (src[i] >= '0' && src[i] <= '9') ||
					   src[i] == '_'))
			{
				size_t len = strlen(result);
				char *tmp = ft_realloc(result, len + 2);
				if (!tmp)
					return free(result), NULL;
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
					return free(result), NULL;
				for (int j = 0; j < key_len; j++)
					key[j] = src[start + j];
				key[key_len] = '\0';
				char *val = ft_get_env(env, key);
				char *tmp = ft_realloc(result, strlen(result) + strlen(val) + 1);
				if (!tmp)
					return free(key), free(result), NULL;
				result = tmp;
				strcat(result, val);
				free(key);
			}
		}
		else
		{
			size_t len = strlen(result);
			char *tmp = ft_realloc(result, len + 2);
			if (!tmp)
				return free(result), NULL;
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

void expand_tokens(t_token **tokens, int *exit_value, t_env *env)
{
	t_token *curr = *tokens;
	t_token *prev = NULL;

	while (curr)
	{
		if (prev && prev->type == HEREDOC)
		{
			prev = curr;
			curr = curr->next;
			continue;
		}

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
				char *expanded = expand_var(curr->value, exit_value, env);
				free(curr->value);
				curr->value = expanded;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}

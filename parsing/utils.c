#include "main.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r');
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while(s2[i] && s1[i])
	{
		if(s2[i] != s1[i])
			return(1);
		i++;
	}
	if(s1[i] || s2[i])
		return(1);
	return(0);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*dst;

	i = 0;
	size = ft_strlen(s1);
	dst = malloc(sizeof(char) * (size + 1));
	if (dst == NULL)
		return (NULL);
	while (i < size)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
        len = slen - start;
	i = 0;
	d = malloc(sizeof(char) * (len + 1));
	if (d == NULL)
		return (NULL);
	while (i < len)
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

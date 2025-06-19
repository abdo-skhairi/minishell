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

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

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

char *ft_itoa(int n)
{
	int tmp = n;
	int len = (n <= 0) ? 1 : 0;

	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	char *str = malloc(len + 1);
	if (!str)
		return NULL;
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
		str[0] = '-';
	while (n)
	{
		str[--len] = '0' + ((n % 10) * (n < 0 ? -1 : 1));
		n /= 10;
	}
	return str;
}

void *ft_realloc(void *ptr, size_t new_size)
{
	if (!ptr)
		return malloc(new_size);
	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}

	char *old = (char *)ptr;
	char *new_ptr = malloc(new_size);
	if (!new_ptr)
		return NULL;
	size_t i = 0;
	while (i + 1 < new_size && old[i])
	{
		new_ptr[i] = old[i];
		i++;
	}
	new_ptr[i] = '\0';
	free(ptr);
	return new_ptr;
}

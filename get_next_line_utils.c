/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:37 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/19 17:39:59 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	if (!str)
		return (0)
	while (str[c] != '\0')
		c++;
	return (c);
}

int	find_n(char *str)
{
	int i;
	
	i =  0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	l1;
	size_t	l2;
	size_t	c;
	size_t	b;

	b = 0;
	c = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = malloc (l1 + l2 + 1 * sizeof(char ));
	if (!res)
		return (NULL);
	while (c < l1)
	{
		res[c] = s1[c];
		c++;
	}
	while (b < l2)
	{
		res[b + c] = s2[b];
		b++;
	}
	res[b + c] = '\0';
	return (res);
}

void free_str(char **str)
{
	free(*str);
	*str = NULL;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	l;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start > l)
		len = 0;
	else if (l - start < len)
		len = l - start;
	res = malloc (len + 1);
	if (!res)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
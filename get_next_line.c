/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:26 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/21 17:37:00 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_str(char *buff, char *contain)
{
	char	*temp;

	temp = ft_strjoin(buff, contain);
	free_str(&buff);
	return (temp);
}

static char	*read_str(int fd, char *buff)
{
	char	*contain;
	ssize_t	byte_readed;

	contain = malloc(BUFFER_SIZE + 1);
	if (!contain)
		return (free_str(&buff), NULL);
	byte_readed = 1;
	while (byte_readed != 0 && find_n(buff) == -1)
	{
		byte_readed = read(fd, contain, BUFFER_SIZE);
		if (byte_readed == -1)
		{
			free_str(&buff);
			free_str(&contain);
			return (NULL);
		}
		contain[byte_readed] = '\0';
		buff = join_str(buff, contain);
		if (!buff)
			return (free_str(&contain), NULL);
	}
	free_str(&contain);
	return (buff);
}

static char	*put_str(char *buff)
{
	char	*str;
	ssize_t	s;

	if (!buff)
		return (NULL);
	if (buff[0] == '\0')
		return (NULL);
	s = find_n(buff);
	if (s >= 0)
		s = s + 1;
	else
		s = (ft_strlen(buff));
	str = ft_substr(buff, 0, s);
	return (str);
}

static char	*str_rest(char *buff)
{
	char	*rest;
	ssize_t	s;
	size_t	len;

	s = find_n(buff);
	if (s >= 0)
		len = ft_strlen(buff) - (s + 1);
	else
	{
		free_str(&buff);
		return (NULL);
	}
	rest = ft_substr(buff, s + 1, len);
	free_str(&buff);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_str(fd, buff);
	if (!buff)
		return (NULL);
	str = put_str(buff);
	if (!str)
	{
		free_str(&buff);
		return (NULL);
	}
	buff = str_rest(buff);
	return (str);
}

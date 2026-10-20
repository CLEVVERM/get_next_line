/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:26 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/20 20:08:12 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_str(int fd, char *buff)
{
	char 	*contain;
	ssize_t	byte_readed;
	char 	*temp;

	contain = malloc(BUFFER_SIZE + 1);
	if (!contain)
		return (NULL);
	byte_readed = 1;
	while (byte_readed != 0 && find_n(buff) == -1)
	{
		byte_readed = read(fd, contain, BUFFER_SIZE);
		if(byte_readed == -1)
		{
			free_str(&buff);
			free_str(&contain);
			return(NULL);
		}
		contain[byte_readed] = '\0';
		temp = buff;
		buff = ft_strjoin(buff, contain);
		if (!buff)
			return (NULL);
		free_str(&temp);
	}
	free_str(&contain);
	return (buff);
}

static char *put_str(char *buff)
{
	char *str;
	ssize_t s;

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

static char *str_rest(char *buff)
{
	char *rest;
	ssize_t s;
	size_t len;

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

char *get_next_line(int fd)
{
	static char *buff;
	char *str;
	int size;

	size = 1;
	str = NULL;
	
}
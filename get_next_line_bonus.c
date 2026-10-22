/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/22 11:39:31 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/22 16:53:09 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*buff[1024];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = read_str(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	str = put_str(buff[fd]);
	if (!str)
	{
		free_str(&buff[fd]);
		return (NULL);
	}
	buff[fd] = str_rest(buff[fd]);
	return (str);
}

// #include <fcntl.h>

// int main(void)
// {
// 	int fd1;
// 	int fd2;
// 	char *buff[1024];
// 	fd2 = open("test1.txt", O_RDONLY);
// 	fd1 = open("test.txt", O_RDONLY);
// 	buff[fd1] = get_next_line(fd1);
// 	buff[fd2] = get_next_line(fd2);
// 	while (buff[fd1] != NULL)
// 	{
// 		printf("%s", buff[fd1]);
// 		free(buff[fd1]);
// 		buff[fd1] = get_next_line(fd1);
// 	}
// 	while (buff[fd2] != NULL)
// 	{
// 		printf("%s", buff[fd2]);
// 		free(buff[fd2]);
// 		buff[fd2] = get_next_line(fd2);
// 	}
// 	close(fd1);
// 	close (fd2);
// }
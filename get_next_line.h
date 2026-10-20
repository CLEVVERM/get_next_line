/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:56 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/20 20:27:49 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
int		find_n(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_str(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
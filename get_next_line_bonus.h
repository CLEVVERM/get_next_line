/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/22 11:43:05 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/22 15:24:02 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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
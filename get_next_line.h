/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:56 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/19 11:28:46 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>

#ifndef	BUFFEE_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd);

#endif
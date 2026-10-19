/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:26 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/19 18:16:14 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char read_str(int fd, char *buff)
{
	char *len;

	len = malloc(BUFFER_SIZE + 1);
}







char *get_next_line(int fd)
{
	static char *buff;
	char *str;
	int size;

	size = 1;
	str = NULL;
	
}
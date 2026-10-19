/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msotnych <msotnych@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/16 15:13:26 by msotnych      #+#    #+#                 */
/*   Updated: 2026/10/19 18:20:34 by msotnych      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char read_str(int fd, char *buff)
{
	char *contain;

	contain = malloc(BUFFER_SIZE + 1);
	if (!contain)
		return (NULL);
}







char *get_next_line(int fd)
{
	static char *buff;
	char *str;
	int size;

	size = 1;
	str = NULL;
	
}
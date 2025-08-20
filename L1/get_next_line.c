/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:53:16 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/19 14:34:44 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd)
{
	static	buffer[BUFFER_SIZE];
	static int	buffer_pos = 0;
	static	int	bytes_read = 0;
	char	*line = NULL;
	int	line_len = 0;
	char	*temp;
	int	i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buffer_pos = 0;
		}
		temp = malloc(line_len + 2);
		if (!temp)
			return (free(line), NULL);
		i = 0;
		while (i < line_len)
		{
			temp[i] = line[i];
			i++;
		}
		temp[line_len] = buffer[buffer_pos];
		temp[line_len + 1] = '\0';
		free(line);
		line = temp;
		line_len++;
		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			return (line);
		}
		buffer_pos++;
	}
	if (line_len == 0)
		return (free(line), NULL);
	return (line);
}

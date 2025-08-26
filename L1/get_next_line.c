/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:19:08 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/18 15:47:58 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos = 0;
	static int	bytes_read = 0;
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

int main()
{
	int fd = open("in", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

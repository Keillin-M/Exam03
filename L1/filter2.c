/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:04:27 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/25 15:35:58 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char	*result = NULL;
	char	*buffer = NULL;
	char	*s = argv[1];
	int	bytes_read = 1;
	int	s_len = strlen(s);
	int	total_size = 0;
	int	capacity = 1024;

	buffer = malloc(capacity);
	if (!buffer)
		return (perror("Error"), 1);
	while (bytes_read > 0)
	{
		bytes_read = read(0, buffer + total_size, capacity - total_size);
		total_size += bytes_read;
		if (total_size >= capacity)
		{
			capacity *= 2;
			buffer = realloc(buffer, capacity);
			if (!buffer)
				return (perror("Error"), 1);
		}
	}
	if (bytes_read < 0)
		return (free(buffer), perror("Error"), 1);
	result = malloc(total_size + 1);
	int	i = 0, j = 0, res_pos = 0;
	
	while (i < total_size)
	{
		char	*found = memmem(buffer + i, total_size - i, s, s_len);
		if (found && found == buffer + i)
		{
			j = 0;
			while (j < s_len)
			{
				result[res_pos] = '*';
				res_pos++;
				j++;
			}
			i += s_len;
		}
		else
			result[res_pos++] = buffer[i++];
	}
	write(1, result, res_pos);
	free(buffer);
	free(result);
	return (0);
}

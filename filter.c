/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:34:46 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/18 14:23:57 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int	bytes_read = 1;

	if (argc != 2 || !argv[1] || !argv[1][0])
		return (1);
	char	*sub = argv[1];
	int	len_sub = strlen(sub);
	char	*buffer = NULL;
	char	*result = NULL;
	int	capacity = 1024;
	int	total_size = 0;

	buffer = malloc(capacity);
	if (!buffer)
		return (perror("Error"), 1);
	while (bytes_read > 0)
	{
		bytes_read = read(0, buffer + total_size, capacity - total_size);
		total_size += bytes_read;
		if (total_size >= capacity -1 )
		{
			capacity *= 2;
			buffer = realloc(buffer, capacity);
			if (!buffer)
				return (perror("Error"), 1);
		}
	}
	if (bytes_read < 0)
	{
		perror("Error");
		free(buffer);
		return (1);
	}
	result = malloc (total_size + 1);
	if (!result)
		return (perror("Error"), 1);
	
	int	i = 0;
	int	j;
	int	res_pos = 0;
	
	while (i < total_size)
	{
		char	*found = memmem(buffer + i, total_size - i, sub, len_sub);
		if (found && found == buffer + i)
		{
			j = 0;
			while (j < len_sub)
			{
				result[res_pos] = '*';
				res_pos++;
				j++;
			}
			i += len_sub;
		}
		else
			result[res_pos++] = buffer[i++];
	}
	write(1, result, res_pos);
	free(buffer);
	free(result);
	return (0);
}

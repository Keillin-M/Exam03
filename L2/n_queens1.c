/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:38:12 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/25 18:45:03 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	is_safe(int *b, int row, int col)
{
	int	i = 0;
	while (i < col)
	{
		if (b[i] == row || b[i] - row == i - col || b[i] - row == col - i)
			return (0);
		i++;
	}
	return (1);
}

void	solve(int *b, int col, int n)
{
	int	i = 0;
	if (col == n)
	{
		while (i < n)
		{
			fprintf(stdout, "%d", b[i]);
			if (i < n - 1)
				fprintf(stdout, " ");
			i++;
		}
		fprintf(stdout, "\n");
	}
	int	row = 0;
	while (row < n)
	{
		if (is_safe(b, row, col))
		{
			b[col] = row;
			solve(b, col + 1, n);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	n = atoi(argv[1]);
	if (n <= 0)
		return (1);
	int	*b = calloc(n, sizeof(int));
	if (!b)
		return (1);
	solve(b, 0, n);
	free(b);
	return (0);
}

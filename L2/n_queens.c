/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:09:28 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/19 17:25:10 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	is_safe(int *board, int row, int col)
{
	int	i = 0;

	while (i < col)
	{
		if (board[i] == row || board[i] - row == i - col || board[i] - row == col - i)
			return (0);
		i++;
	}
	return (1);
}

void	solve(int *board, int col, int n)
{
	int	i = 0;

	if (col == n)
	{
		while (i < n)
		{
			fprintf(stdout, "%d", board[i]);
			if (i < n - 1)
				fprintf(stdout, " ");
			i++;
		}
		fprintf(stdout, "\n");
		return ;
	}
	int	row = 0;
	while (row < n)
	{
		if (is_safe(board, row, col))
		{
			board[col] = row;
			solve(board, col + 1, n);
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
	int	*board = calloc(n, sizeof(int));
	if (!board)
		return (1);
	solve(board, 0, n);
	free(board);
	return (0);
}

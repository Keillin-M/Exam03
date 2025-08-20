/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:30:31 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/19 18:16:34 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	powerset(int *a, int n, int target, int *sub, int size, int i, int sum)
{
	int	j;

	if (sum == target)
	{
		j = 0;
		while (j < size)
		{
			if (j)
				printf(" %d", sub[j]);
			else
				printf("%d", sub[j]);
			j++;
		}
		printf("\n");
	}
	int	i = 0;
	while (i < n)
	{
		sub[size] = a[i];
		powerset(a, n, target, sub, size + 1, i + 1, sum + a[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	int	target = atoi(argv[1]), n = argc - 2, a[100], sub[100];
	int	i = 0;
	while (i < n)
	{
		a[i] = atoi(argv[i + 2]);
		i++;
	}
	powerset(a, n, target, sub, 0, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:14:24 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/25 19:23:00 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	solve(char *s, int i, int left, int right, char *result, int len)
{
	if (!s[i])
	{
		if (!left && !right)
		{
			result[len] = 0;
			int	balance = 0, j= 0;
			while (result[j])
			{
				if (result[j] == '(')
					balance++;
				else if (result[j] == ')')
					balance--;
				if (balance < 0)
					return ;
				j++;
			}
			if (!balance)
				puts(result);
		}
		return ;
	}
	char	c = s[i];
	if ((c == '(' && left > 0) || (c == ')' && right > 0))
	{
		result[len] = ' ';
		int	new_left = left;
		int	new_right = right;
		if (c == '(')
			new_left--;
		if (c == ')')
			new_right--;
		solve(s, i + 1, new_left, new_right, result, len + 1);
	}
	result[len] = c;
	solve(s, i + 1, left, right, result, len + 1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char	*s = argv[1];
	int	i = 0, left = 0, right = 0;
	while (s[i])
	{
		if (s[i] == '(')
			left++;
		else if (s[i] == ')')
		{
			if (left > 0)
				left--;
			else
				right++;
		}
		i++;
	}
	char	result[10000];
	solve(s, 0, left, right, result, 0);
	return (0);
}

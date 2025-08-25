/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:48:45 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/25 17:58:49 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	swap(char *a, char *b)
{
	char	temp = *a;
	*a = *b;
	*b = temp;
}

void	print_str(const char *s)
{
	size_t	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	write(1, "\n", 1);
}

void	backtrack(char *s, int start, int len)
{
	if (start == len)
	{
		print_str(s);
		return ;
	}
	int	i = start;
	while (i < len)
	{
		swap(&s[start], &s[i]);
		backtrack(s, start + 1, len);
		swap(&s[start], &s[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	i = 0, j = 0, len = 0;
	char	*str = argv[1];
	while(str[len])
		len++;
	char	*s = NULL;
	s = malloc(len + 1);
	if (!s)
		return (1);
	while (i <= len)
	{
		s[i] = str[i];
		i++;
	}
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (s[i] > s[j])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
	backtrack(s, 0, len);
	free(s);
	return (0);
}

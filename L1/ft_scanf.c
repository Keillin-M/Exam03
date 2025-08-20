/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaeda <kmaeda@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:53:20 by kmaeda            #+#    #+#             */
/*   Updated: 2025/08/19 16:27:17 by kmaeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int	match_space(FILE *f)
{
	int	c;
	int	found_space = 0;

	while ((c = fgetc(f)) != EOF && isspace(c))
		found_space = 1;
	if (c != EOF)
		ungetc(c, f);
	if (c == EOF)
		return (-1);
	else if (found_space)
		return (1);
	else
		return (0);
}

int	match_char(FILE *f, char target)
{
	int	c = fgetc(f);

	if (c == EOF)
		return (-1);
	if (c == target)
		return (1);
	ungetc(c, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*ptr = va_arg(ap, char *);
	int	c = fgetc(f);

	if (c == EOF)
		return (-1);
	*ptr = c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int	*ptr = va_arg(ap, int *);
	int	c, sign = 1, num = 0, digits = 0;

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	if (c == '-')
	{
		sign = -1;
		c = fgetc(f);
	}
	else if (c == '+')
		c = fgetc(f);
	while (c != EOF && isdigit(c))
	{
		num = num * 10 + (c - '0');
		digits = 1;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (!digits)
	{
		if (c == EOF)
			return (-1);
		return (0);
	}
	*ptr = num * sign;
		return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*ptr = va_arg(ap, char *);
	int	c, count = 0;

	while ((c = fgetc(f)) != EOF && !isspace(c))
		ptr[count++] = c;
	if (c != EOF)
		ungetc(c, f);
	if (count == 0)
		return (0);
	ptr[count] = '\0';
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
/*
int	main()
{
	int	n; 

	printf("Enter number: "); 
	int	r = ft_scanf("%d", &n); 
	printf("Got: result=%d, num=%d\n", r, n);
	printf("Enter number: "); 
	int	s = scanf("%d", &n); 
	printf("Got: result=%d, num=%d\n", s, n);

	char ch;
	
	printf("Enter char: ");
	printf("Char result: %d, value: '%c'\n", ft_scanf(" %c", &ch), ch);
	printf("Enter char: ");
	printf("Char result: %d, value: '%c'\n", scanf(" %c", &ch), ch);

	char str[50];
	
	printf("Enter word: ");
	printf("String result: %d, value: \"%s\"\n", ft_scanf("%s", str), str);
	printf("Enter word: ");
	printf("String result: %d, value: \"%s\"\n", scanf("%s", str), str);

	return 0; 
}*/

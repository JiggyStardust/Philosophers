/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:16 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/30 09:18:42 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	else
		return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (*str)
	{
		if (write(1, str, 1) != 1)
			return (-1);
		count++;
		str++;
	}
	return (count);
}

static int	check_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count = ft_putnbr(va_arg(ap, int), &count);
	else if (specifier == 'u')
		count = ft_putunsigned(va_arg(ap, unsigned int), &count);
	else if (specifier == 'p')
		count += ft_putptr(va_arg(ap, void *));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_puthexadec(va_arg(ap, unsigned int), specifier);
	else if (specifier == '%')
	{
		if (write(1, "%", 1) != 1)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, s);
	count = 0;
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			count += check_format(*s, ap);
			if (count < 0)
				return (-1);
		}
		else
		{
			if (write(1, s, 1) != 1)
				return (-1);
			count++;
		}
		s++;
	}
	va_end(ap);
	return (count);
}

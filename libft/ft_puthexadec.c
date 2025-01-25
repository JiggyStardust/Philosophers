/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexadec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:34:25 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/30 09:20:33 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_len(unsigned long n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static int	ft_dec_to_hex(unsigned long n, const char *hex_digits)
{
	char	temp[16];
	int		i;

	i = 0;
	while (n > 0)
	{
		temp[i] = hex_digits[n % 16];
		n = n / 16;
		i++;
	}
	while (i-- > 0)
	{
		if (ft_putchar(temp[i]) < 0)
			return (-1);
	}
	return (1);
}

int	ft_puthexadec(unsigned long n, int specifier)
{
	int		len;

	len = ft_hex_len(n);
	if (n == 0)
	{
		if (write(1, "0", 1) < 0)
			return (-1);
		return (1);
	}
	if (specifier == 'X')
	{
		if (ft_dec_to_hex(n, HEXADEC_UPPER) < 0)
			return (-1);
	}
	else if (specifier == 'x')
	{
		if (ft_dec_to_hex(n, HEXADEC_LOWER) < 0)
			return (-1);
	}
	return (len);
}

int	ft_putptr(void *p)
{
	uintptr_t	ptr;
	int			len;

	len = 0;
	ptr = (uintptr_t)p;
	len += write(1, "0x", 2);
	if (len != 2)
		return (-1);
	if (ptr == 0)
	{
		if (write(1, "0", 1) < 0)
			return (-1);
		return (len + 1);
	}
	len += ft_puthexadec(ptr, 'x');
	return (len);
}

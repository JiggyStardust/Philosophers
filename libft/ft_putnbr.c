/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:53:44 by sniemela          #+#    #+#             */
/*   Updated: 2024/08/06 09:54:10 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsigned(unsigned int n, int *count)
{
	if (n < 10)
	{
		if (ft_putchar(n + '0') != 1)
			return (-1);
		(*count)++;
	}
	else
	{
		if (ft_putunsigned(n / 10, count) < 0)
			return (-1);
		if (ft_putunsigned(n % 10, count) < 0)
			return (-1);
	}
	return (*count);
}

int	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) != 11)
			return (-1);
		return (11);
	}
	if (n < 0)
	{
		if (ft_putchar('-') != 1)
			return (-1);
		n = -n;
		(*count)++;
	}
	*count = ft_putunsigned(n, count);
	if (*count < 0)
		return (-1);
	return (*count);
}

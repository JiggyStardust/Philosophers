/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:26:45 by sniemela          #+#    #+#             */
/*   Updated: 2024/05/06 11:09:47 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;
	size_t	total_size;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	i = 0;
	total_size = count * size;
	str = (char *)malloc(sizeof(char) * (total_size));
	if (!str)
		return (NULL);
	while (i < total_size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

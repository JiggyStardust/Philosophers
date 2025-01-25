/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:35:03 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:48:55 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (ft_strlen(needle) == 0 || needle == NULL)
		return ((char *)haystack);
	if (len <= 0)
		return (NULL);
	while (haystack[j] != '\0' && j < len)
	{
		i = 0;
		while (needle[i] == haystack[j + i] && needle[i] != '\0' && j + i < len)
		{
			i++;
		}
		if (needle[i] == '\0')
			return ((char *)haystack + j);
		j++;
	}
	return (NULL);
}

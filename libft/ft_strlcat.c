/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:01:47 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:46:20 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	u;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	u = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dstsize == 0 && !dest)
		return (src_len);
	while (dest[i] != '\0')
	{
		i++;
	}
	while (dstsize > i + 1 && src[u])
	{
		dest[i] = src[u];
		u++;
		i++;
	}
	dest[i] = '\0';
	if (dstsize < dest_len)
		return (dstsize + src_len);
	return (dest_len + src_len);
}

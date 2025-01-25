/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:30:54 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:49:52 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ret;
	int		i;

	start = 0;
	i = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen((char *)s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]))
		start++;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	if (ret == NULL)
		return (NULL);
	while (i < end - start + 1)
	{
		ret[i] = s1[i + start];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

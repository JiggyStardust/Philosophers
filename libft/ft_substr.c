/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:27:57 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:50:14 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start > len)
		s_len = len;
	else
		s_len = s_len - start;
	subs = (char *)malloc(sizeof(char) * s_len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		subs[i] = (char)s[start];
		i++;
		start++;
	}
	subs[i] = '\0';
	return (subs);
}

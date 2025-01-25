/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:28:59 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:45:45 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str_joined = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_joined)
		return (NULL);
	while (s1[i] != '\0')
	{
		str_joined[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str_joined[i] = s2[j];
		i++;
		j++;
	}
	str_joined[i] = '\0';
	return (str_joined);
}

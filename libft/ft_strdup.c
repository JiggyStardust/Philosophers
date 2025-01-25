/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:43:50 by sniemela          #+#    #+#             */
/*   Updated: 2024/07/29 13:43:40 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*target;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	target = (char *)malloc(sizeof(char) * (len + 1));
	if (!target)
		return (NULL);
	while (s1[i] != '\0')
	{
		target[i] = s1[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:00:44 by sniemela          #+#    #+#             */
/*   Updated: 2024/05/03 08:58:01 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		nodes;
	t_list	*temp;

	nodes = 0;
	temp = lst;
	while (temp)
	{
		nodes++;
		temp = temp->next;
	}
	return (nodes);
}

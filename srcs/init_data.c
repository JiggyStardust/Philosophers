/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:08:30 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/20 09:26:01 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*assign_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!forks)
		return (NULL);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (false);
	data->forks = assign_forks(data);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->lock);
		return (false);
	}
	return (true);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!assign_data_nums(av, data))
	{
		free (data);
		return (NULL);
	}
	data->quit = false;
	if (!init_mutexes(data))
	{
		free(data);
		return (NULL);
	}
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:08:30 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/08 12:30:35 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*assign_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int	i;

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

int	get_time_ms(void)
{
	int				time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Couldn't get current time.\n");
		return (0);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

t_data	*init_data(char **av)
{
	t_data	*data;
	int		err;

	err = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!assign_data_nums(av, data))
	{
		free (data);
		return (NULL);
	}
	data->philo_died = false;
	data->quit = false;
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		free(data);
		return (NULL);
	}
	data->forks = assign_forks(data);
	if (!data->forks)
	{
		free (data);
		return (NULL);
	}
	return (data);
}

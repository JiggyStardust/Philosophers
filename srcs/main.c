/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:06 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/06 16:56:17 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_destroy_forks(pthread_mutex_t *forks, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
		i--;
	}
	free(forks);
}

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

	if (gettimeofday(&tv, NULL) == 0)
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
	data->forks = assign_forks(data);
	if (!data->forks)
	{
		free (data);
		return (NULL);
	}
	return (data);
}
/*
t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
}
*/

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	philo = NULL;
	if (!argument_check(ac))
		return (1);
	data = init_data(av);
	if (!data)
		return (1);
	// philo = init_philos(data);
	if (!philo)
	{
//		free_data(data);
		return (1);
	}
	return (0);
}

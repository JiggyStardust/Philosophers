/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:06 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/20 09:31:35 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*single_philo(t_philo *philo)
{
	thinking(philo);
	if (!take_first_fork(philo))
		return (NULL);
	usleep(philo->data->time_dies * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->lock);
	gettimeofday(&time, NULL);
	if (philo->data->num_philos == 1)
		return (single_philo(philo));
	thinking(philo);
	if (philo->id % 2 == 0)
		usleep(time.tv_usec % 3000 + 1000);
	while (true)
	{
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		thinking(philo);
		usleep(time.tv_usec % 3000 + 1000);
	}
	return (NULL);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!philo)
		return (NULL);
	while (i < data->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = 0;
		philo[i].meals_eaten = 0;
		philo[i].data = data;
		philo[i].right_fork = &data->forks[i];
		if (i == 0)
			philo[i].left_fork = &data->forks[data->num_philos - 1];
		else
			philo[i].left_fork = &data->forks[i - 1];
		i++;
	}
	return (philo);
}

bool	start_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock);
	while (i < data->num_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine,
				(void *)&philo[i]) != 0)
		{
			data->quit = true;
			printf("pthread_create fail.\n");
			pthread_mutex_unlock(&data->lock);
			cleanup_philo(philo, i - 1);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&data->lock);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!argument_check(ac))
		return (1);
	data = init_data(av);
	if (!data)
		return (1);
	philo = init_philos(data);
	if (!philo)
	{
		free_data(data);
		return (1);
	}
	if (start_threads(data, philo))
	{
		monitoring(philo, data);
		cleanup_philo(philo, data->num_philos - 1);
	}
	free_data(data);
	return (0);
}

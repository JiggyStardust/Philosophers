/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:06 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/18 09:32:10 by sniemela         ###   ########.fr       */
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
	int				delay;
	struct timeval	time;

	philo = (t_philo *)arg;
	gettimeofday(&time, NULL);
	if (philo->data->num_philos == 1)
		return (single_philo(philo));
	delay = 0;
	if (philo->id % 2 == 0)
		delay = time.tv_usec % 3000 + 1000;
	thinking(philo);
	usleep(delay);
	while (true)
	{
		if (eating(philo))
			if (sleeping(philo))
				thinking(philo);
		if (philo_quit(philo))
			return (NULL);
		gettimeofday(&time, NULL);
		usleep(time.tv_usec % 3000 + 1000);
	}
	return (NULL);
}

static void	assign_philo_nums_and_forks(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten = 0;
	philo->data = data;
	philo->right_fork = &data->forks[i];
	if (i == 0)
		philo->left_fork = &data->forks[data->num_philos - 1];
	else
		philo->left_fork = &data->forks[i - 1];
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!philo)
		return (NULL);
	data->start_time = get_time_ms();
	while (i < data->num_philos)
	{
		assign_philo_nums_and_forks(&philo[i], data, i);
		if (pthread_create(&philo[i].thread, NULL, &routine,
				(void *)&philo[i]) != 0)
		{
			cleanup_philo(philo, i - 1);
			return (NULL);
		}
		i++;
	}
	return (philo);
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
	monitoring(philo, data);
	cleanup_philo(philo, data->num_philos - 1);
	free_data(data);
	return (0);
}

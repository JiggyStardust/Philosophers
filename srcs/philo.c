/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:06 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/08 10:50:28 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		monitoring(t_philo *philo)
{
	if (philo->data->philo_died)
	{
		printf("%d %d died\n", get_time_ms() - philo->data->start_time, philo->id);
		return (0);
	}
	return (1);
}

void	thinking(t_philo *philo)
{
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
	{
		philo->data->philo_died = true ;
		return ;
	}
	if (!philo->is_thinking)
	{
		printf("%d %d is thinking\n", get_time_ms() - philo->data->start_time, philo->id);
		philo->is_thinking = true;
	}

}

int	eating(t_philo *philo)
{
	if (philo->data->philo_died)
		return (0);
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
	{
		philo->data->philo_died = true ;
		return (0);
	}
	if (philo->id % 2 == 1)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (0);
		printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (0);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (0);
		printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (0);
	}
	printf("%d %d is eating\n", get_time_ms() - philo->data->start_time, philo->id);
	usleep(philo->data->time_eats * 1000);
	philo->last_meal_time = get_time_ms();
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (0);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (0);
	return (1);

}

void	sleeping(t_philo *philo)
{
	if (philo->data->philo_died)
		return ;
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
	{
		philo->data->philo_died = true ;
		return ;
	}
	printf("%d %d is sleeping.\n", get_time_ms() - philo->data->start_time, philo->id);
	usleep(philo->data->time_sleeps * 1000);
}

void	*routine(void *arg)
{
	t_philo *philo;
	int 	i;

	philo = (t_philo *)arg;
	i = 0;
	while (monitoring(philo))
	{
		thinking(philo);
		if (eating(philo))
			sleeping(philo);
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
		philo[i].data = data;
		philo[i].right_fork = &data->forks[i];
		if (i == 0)
			philo[i].left_fork = &data->forks[data->num_philos - 1];
		else
			philo[i].left_fork = &data->forks[i - 1];
		philo[i].last_meal_time = get_time_ms();
		philo[i].meals_eaten = 0;
		philo[i].is_thinking = false;
		if (pthread_create(&philo[i].thread, NULL, &routine, (void *)&philo[i]) != 0)
		{
			cleanup_philo(philo, i - 1);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (philo);
}

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
	philo = init_philos(data);
	if (!philo)
	{
		free_data(data);
		return (1);
	}
	return (0);
}

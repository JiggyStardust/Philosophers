/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:11:24 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/11 15:48:44 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_starved(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (false);
	}
}

bool	philo_dead(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (philo_starved(&philo[i]))
		{
			pthread_mutex_lock(&data->lock);
			if (!data->quit && pthread_mutex_lock(&data->print) == 0)
			{
				if (!data->quit)
				{
					printf("%d %d died\n", get_time_ms() - data->start_time, \
						philo[i].id);
					data->quit = true;
				}
				pthread_mutex_unlock(&data->lock);
				pthread_mutex_unlock(&data->print);
			}
			return (true);
		}
		i++;
	}
	return (false);
}

bool	philo_is_full(t_philo *philo, t_data *data)
{
	bool	ret;

	ret = false;
	if (data->num_must_eat == -1)
		return (ret);
	pthread_mutex_lock(&data->lock);
	if (philo->meals_eaten >= data->num_must_eat)
		ret = true;
	pthread_mutex_unlock(&data->lock);
	return (ret);
}

bool	philos_are_full(t_philo *philo, t_data *data)
{
	int	fullness;
	int	i;

	fullness = 0;
	i = 0;
	while (i < data->num_philos)
	{
		if (philo_is_full(&philo[i], data))
			fullness++;
		if (fullness == data->num_philos)
		{
			pthread_mutex_lock(&data->lock);
			data->quit = true;
			pthread_mutex_unlock(&data->lock);
			return (true);
		}
		i++;
	}
	return (false);
}

void	monitoring(t_philo *philo, t_data *data)
{
	while (1)
	{
		if (philo_dead(philo, data))
			break ;
		if (philos_are_full(philo, data))
		{
			pthread_mutex_lock(&data->print);
			printf("Philosophers full, ending simulation\n");
			pthread_mutex_unlock(&data->print);
			break ;
		}
	}
}

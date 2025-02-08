/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:11:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/08 13:05:10 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
bool	philo_died(t_philo *philo)
{
	if (philo->data->philo_died)
		return (true);
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
	{
		philo->data->philo_died = true ;
		return (true);
	}
	return (false);
}

int	eating(t_philo *philo)
{
	if (philo_died(philo))
		return (0);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!philo_died(philo))
			printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!philo_died(philo))
		{
			printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->left_fork);
	}
	printf("%d %d is eating\n", get_time_ms() - philo->data->start_time, philo->id);
	usleep(philo->data->time_eats * 1000);
	philo->last_meal_time = get_time_ms();
	if (pthread_mutex_unlock(philo->left_fork) != 0 || philo_died(philo))
		return (0);
	if (pthread_mutex_unlock(philo->right_fork) != 0 || philo_died(philo))
		return (0);
	return (1);
}

void	sleeping(t_philo *philo)
{
	if (philo_died(philo))
		return ;
	printf("%d %d is sleeping.\n", get_time_ms() - philo->data->start_time, philo->id);
	usleep(philo->data->time_sleeps * 1000);
	philo->is_thinking = false;
}

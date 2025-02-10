/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:11:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/10 17:17:59 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	if (philo_died(philo))
		return ;
	if (!philo->is_thinking)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d is thinking\n", get_time_ms() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		philo->is_thinking = true;
	}
}

bool	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->philo_died)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->lock);
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
		return (true);
	return (false);
}

bool	take_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!philo_died(philo))
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
		return (true);
	}
	pthread_mutex_lock(philo->right_fork);
	if (!philo_died(philo))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

bool	take_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!philo_died(philo))
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		return (true);
	}
	pthread_mutex_lock(philo->left_fork);
	if (!philo_died(philo))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d has taken a fork\n", get_time_ms() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	return (true);
}

int	philo_ate(t_philo *philo)
{
	int	time;

	time = get_time_ms();
	while (get_time_ms() < time + philo->data->time_eats)
	{
		usleep(1);
		if (philo_died(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
	}
	return (1);
}

int	eating(t_philo *philo)
{
	if (philo_died(philo))
		return (0);
	if (!take_first_fork(philo))
		return (0);
	if (!take_second_fork(philo))
		return (0);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d is eating\n", get_time_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (!philo_ate(philo))
		return (0);
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	sleeping(t_philo *philo)
{
	if (philo_died(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d is sleeping.\n", get_time_ms() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->data->print);
	usleep(philo->data->time_sleeps * 1000);
	philo->is_thinking = false;
}

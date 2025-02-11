/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:32:32 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/11 10:33:27 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	take_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!philo_quit(philo))
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
	if (!philo_quit(philo))
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
		if (!philo_quit(philo))
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
	if (!philo_quit(philo))
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

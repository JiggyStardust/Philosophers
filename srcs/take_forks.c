/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:32:32 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/18 10:11:40 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	first_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->print);
	if (!philo_quit(philo))
	{
		printf("%d %d has taken a fork\n", get_time_ms() \
				- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(philo->left_fork);
	return (false);
}

bool	take_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (first_fork_odd(philo));
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->print);
		if (!philo_quit(philo))
		{
			printf("%d %d has taken a fork\n", get_time_ms() \
				- philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print);
			return (true);
		}
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
}

static bool	second_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->print);
	if (!philo_quit(philo))
	{
		printf("%d %d has taken a fork\n", get_time_ms() \
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (false);
}

bool	take_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (second_fork_odd(philo));
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->data->print);
		if (!philo_quit(philo))
		{
			printf("%d %d has taken a fork\n", get_time_ms() \
				- philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print);
			return (true);
		}
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
}

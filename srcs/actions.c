/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:11:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/14 10:43:51 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_quit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->quit)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (false);
}

void	thinking(t_philo *philo)
{
	if (philo_quit(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (!philo_quit(philo))
		printf("%d %d is thinking\n", get_time_ms() \
			- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

static bool	philo_ate(t_philo *philo)
{
	bool	ate;

	ate = true;
	if (!ft_sleep(philo, philo->data->time_eats))
		ate = false;
	else
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (ate);
}

bool	eating(t_philo *philo)
{
	if (philo_quit(philo))
		return (false);
	if (!take_first_fork(philo))
		return (false);
	if (!take_second_fork(philo))
		return (false);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->lock);
	if (!philo_quit(philo))
		printf("%d %d is eating\n", get_time_ms() \
			- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (!philo_ate(philo))
		return (false);
	return (true);
}

bool	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo_quit(philo))
		printf("%d %d is sleeping\n", get_time_ms() \
			- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (!ft_sleep(philo, philo->data->time_sleeps))
		return (false);
	return (true);
}

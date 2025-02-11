/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:11:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/11 15:47:03 by sniemela         ###   ########.fr       */
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
	if (get_time_ms() - philo->last_meal_time >= philo->data->time_dies)
		return (true);
	return (false);
}

void	thinking(t_philo *philo)
{
	if (philo_quit(philo))
		return ;
	if (!philo->is_thinking)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d is thinking\n", get_time_ms() \
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		philo->is_thinking = true;
	}
}

int	philo_ate(t_philo *philo)
{
	int	time;

	time = get_time_ms();
	while (get_time_ms() < time + philo->data->time_eats)
	{
		usleep(1);
		if (philo_quit(philo))
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
	if (philo_quit(philo))
		return (0);
	if (!take_first_fork(philo))
		return (0);
	if (!take_second_fork(philo))
		return (0);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d is eating\n", get_time_ms() \
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (!philo_ate(philo))
		return (0);
	pthread_mutex_lock(&philo->data->lock);
	philo->meals_eaten++;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

void	sleeping(t_philo *philo)
{
	int	time;

	time = get_time_ms();
	if (philo_quit(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	printf("%d %d is sleeping.\n", get_time_ms() \
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	while (get_time_ms() < time + philo->data->time_sleeps)
	{
		if (philo_quit(philo))
			return ;
		usleep(1);
	}
	philo->is_thinking = false;
}

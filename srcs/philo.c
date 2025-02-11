/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:15:06 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/11 10:31:11 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *philo;
	int 	i;

	philo = (t_philo *)arg;
	i = 0;
	while (true)
	{
		thinking(philo);
		if (eating(philo))
			sleeping(philo);
		if (philo_quit(philo))
			break ;
	}
	return (NULL);
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * data->num_philos);
	if (!philo)
		return (NULL);
	while (i < data->num_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->data = data;
		philo[i]->right_fork = &data->forks[i];
		if (i == 0)
			philo[i]->left_fork = &data->forks[data->num_philos - 1];
		else
			philo[i]->left_fork = &data->forks[i - 1];
		philo[i]->last_meal_time = get_time_ms();
		philo[i]->meals_eaten = 0;
		philo[i]->is_thinking = false;
		if (pthread_create(&philo[i]->thread, NULL, &routine, (void *)philo[i]) != 0)
		{
			cleanup_philo(philo, i - 1);
			return (NULL);
		}
		i++;
	}
	return (philo);
}

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

bool	philo_dead(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (philo_starved(philo[i]))
		{
			pthread_mutex_lock(&data->lock);
			data->philo_died = true;
			pthread_mutex_unlock(&data->lock);
			if (!data->quit && pthread_mutex_lock(&data->print) == 0)
			{
				if (!data->quit)
				{
					printf("%d %d died\n", get_time_ms() - data->start_time,
					philo[i]->id);
					data->quit = true;
				}
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
	if (data->num_must_eat == 0)
		return (ret);
	pthread_mutex_lock(&data->lock);
	if (philo->meals_eaten >= data->num_must_eat)
		ret = true;
	pthread_mutex_unlock(&data->lock);
	return (ret);
}

bool	philos_are_full(t_philo **philo, t_data *data)
{
	int	fullness;
	int	i;

	fullness = 0;
	i = 0;
	while (i < data->num_philos)
	{
		if (philo_is_full(philo[i], data))
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

void	monitoring(t_philo **philo, t_data *data)
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

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philo;

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

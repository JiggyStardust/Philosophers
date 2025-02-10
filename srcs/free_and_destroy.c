/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:33:35 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/10 16:09:04 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_destroy_forks(pthread_mutex_t *forks, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
		i--;
	}
	free(forks);
}

void	free_data(t_data *data)
{
	free_destroy_forks(data->forks, data->num_philos - 1);
	pthread_mutex_destroy(&data->print);
	free(data);
}

void	cleanup_philo(t_philo **philo, int i)
{
	while (i >= 0)
	{
		// printf("before pthread_join with philo %d\n", i + 1);
		pthread_join(philo[i]->thread, NULL);
		// printf("after pthread_join with philo %d\n", i + 1);
		free(philo[i]);
		i--;
	}
	free(philo);
}

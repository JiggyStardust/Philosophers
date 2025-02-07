/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:33:35 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/07 17:10:53 by sniemela         ###   ########.fr       */
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
	free(data);
}
void	cleanup_philo(t_philo *philo, int i)
{
	while (i >= 0)
	{
		pthread_join(philo[i].thread, NULL);
		i--;
	}
	free(philo);
}

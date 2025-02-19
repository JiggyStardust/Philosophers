/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:36:25 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/19 12:38:40 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time_ms(void)
{
	int				time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Couldn't get current time.\n");
		return (0);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	argument_check(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Mandatory arguments (4 in total) are:\n");
		printf("number_of_philosophers\n");
		printf("time_to_die\n");
		printf("time_to_eat\n");
		printf("time_to_sleep\n");
		printf("\nOptional:\n");
		printf("number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	return (1);
}

bool	ft_sleep(t_philo *philo, int time)
{
	int	start_time;

	start_time = get_time_ms();
	while (get_time_ms() < start_time + time)
	{
		if (philo_quit(philo))
			return (false);
		usleep(250);
	}
	return (true);
}

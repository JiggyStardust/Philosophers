/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:28:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/07 17:11:11 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // creating threads
# include <sys/time.h> // gettimeofday()
# include <unistd.h> // usleep()
# include <stdio.h> // printf()
# include <string.h> // memset
# include <stdlib.h> // malloc
# include <stdbool.h> // bool

typedef struct s_data
{
	int				time_sleeps;
	int				time_eats;
	int				time_dies;
	int				num_philos;
	int				num_must_eat;
	int				start_time;
	bool			philo_died;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

/******************************************************************************
 * Checks if there's a valid amount of arguments, but doesn't check the 
 * validity of them (happens later)
******************************************************************************/
int	argument_check(int ac);

/******************************************************************************
 * Assign all int values inside @param s_data struct. Arguments (char argv[i]) 
 * are checked and turned into ints using a static function ft_atoi_error().
 * @param start_time we get by calling get_time_ms() function.
 *****************************************************************************/
int	assign_data_nums(char **av, t_data *data);

/******************************************************************************
 * Returns the current time in milliseconds by calling gettimeofday() and
 * converting the result into milliseconds.
 *****************************************************************************/
int	get_time_ms(void);

/******************************************************************************
 * Destroys fork mutexes, free's *forks and ultimately frees t_data struct.
 ******************************************************************************/
void	free_data(t_data *data);

void	cleanup_philo(t_philo *philo, int i);

void	free_destroy_forks(pthread_mutex_t *forks, int i);

t_data	*init_data(char **av);

pthread_mutex_t	*assign_forks(t_data *data);

#endif
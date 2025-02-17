/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:28:26 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/17 09:29:21 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // creating threads
# include <sys/time.h> // gettimeofday()
# include <unistd.h> // usleep()
# include <limits.h>  // INT_MAX
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
	bool			quit;
	bool			start;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
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
int				argument_check(int ac);

/******************************************************************************
 * Assign all int values inside @param s_data struct. Arguments (char argv[i]) 
 * are checked and turned into ints using a static function ft_atoi_error().
 * @param start_time we get by calling get_time_ms() function.
 *****************************************************************************/
int				assign_data_nums(char **av, t_data *data);

/******************************************************************************
 * Initializes and returns an array of mutexes (= *forks). There are as many
 * mutexes, as there are philosophers = as there are forks.
******************************************************************************/
pthread_mutex_t	*assign_forks(t_data *data);

/******************************************************************************
 * Destroys the threads by calling pthread_join() and frees the t_philo struct.
******************************************************************************/
void			cleanup_philo(t_philo *philo, int i);

/******************************************************************************
 * Destroys fork mutexes by calling free_destroy_forks() and ultimately frees 
 * t_data struct.
******************************************************************************/
void			free_data(t_data *data);

/******************************************************************************
 * Destroys fork mutexes by calling pthread_mutex_destroy() frees *forks array.
******************************************************************************/
void			free_destroy_forks(pthread_mutex_t *forks, int i);

/******************************************************************************
 * Helper function to perform usleep() for readability and checking whether the
 * program should quit running whilst eating or sleeping.
******************************************************************************/
bool			ft_sleep(t_philo *philo, int time);

/******************************************************************************
 * Returns the current time in milliseconds by calling gettimeofday() and
 * converting the result into milliseconds.
******************************************************************************/
int				get_time_ms(void);

/******************************************************************************
 * Allocates memory for t_data struct and assigns it's values by calling
 * assign_data_nums() and assign_forks().
******************************************************************************/
t_data			*init_data(char **av);

/******************************************************************************
 * Monitors if the philos are starved (get_time_ms() - last_meal exceeds 
 * the time_dies), or if all the philos have eaten enough -> quits the simula-
 * tion without a message.
******************************************************************************/
void			monitoring(t_philo *philo, t_data *data);

/******************************************************************************
 * Check whether the main thread has detected a death of a philo, or is every 
 * philo is full. Returns true if philo-data->quit == true, false if not.
******************************************************************************/
bool			philo_quit(t_philo *philo);

/******************************************************************************
 * Makes philo pthread_mutex_lock the left_fork for odd numbered philos, and 
 * the right_fork for even numbered philos.
******************************************************************************/
bool			take_second_fork(t_philo *philo);

/******************************************************************************
 * Makes philo pthread_mutex_lock the right_fork for odd numbered philos, and 
 * the left_fork for even numbered philos.
******************************************************************************/
bool			take_first_fork(t_philo *philo);

/******************************************************************************
 * The eating process of a philo, calls take_first_fork, take_second_fork and 
 * starts to eat.
******************************************************************************/
bool			eating(t_philo *philo);

/******************************************************************************
 * The sleeping process, which happens after eating. Returns true if succeeded
 * to sleep the required.
******************************************************************************/
bool			sleeping(t_philo *philo);

/******************************************************************************
 * The thinking process, which is occuring whenever philo doesn't eat or sleep.
******************************************************************************/
void			thinking(t_philo *philo);

#endif
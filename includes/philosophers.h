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
	bool			philo_died;
	long long		start_time;
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

int	ft_atoi(const char *str);
#endif
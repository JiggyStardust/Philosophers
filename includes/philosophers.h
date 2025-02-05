#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h> // creating threads
# include <sys/time.h> // gettimeofday()
# include <unistd.h> // usleep()
# include <stdio.h> // printf()
# include <string.h> // memset
# include <stdlib.h> // malloc
# include <stdbool.h> // bool

typedef struct s_philo
{
	int	sleep;
	int	eat;
	int	death;
	int	philo_i;
	int	philos;
	int	meals;
	bool	dead;
}	t_philo;

int	ft_atoi(const char *str);
#endif
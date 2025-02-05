#include "philosophers.h"

void	invalid_argument_amount(void)
{
	printf("Mandatory arguments (4 in total) are:\n");
	printf("number_of_philosophers\n");
	printf("time_to_die\n");
	printf("time_to_eat\n");
	printf("time_to_sleep\n");
	printf("\nOptional:\n");
	printf("number_of_times_each_philosopher_must_eat\n");
}

static int(valid_argument(char *str))
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		printf("Argument values should be positive.\n");
		return (0);
	}
	else if (str[0] == '+' &&(str[1] < '0'|| str[1] > '9'))
	{
		printf("Argument value contained invalid characters.\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] < '0'|| str[i] > '9')
		{
			printf("Argument(s) contained invalid characters.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_atoi_error(char *str, int *err)
{
	int		i;
	long	result;
	long	check;

	i = 0;
	result = 0;
	check = result;
	if ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)) // can it contain w
		i++;
	if (!valid_argument(str + i))
	{
		*err = 1;
		return (0);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
		if (check > result) // if it exceeds long, should this be done?
			return (-1);
	}
	return ((int)result);
}

t_philo	*init_philos(char **av)
{
	t_philo	*philo;
	int		err;

	err = 0;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philos = ft_atoi_error(av[1], &err);
	philo->death = ft_atoi_error(av[2], &err);
	philo->eat = ft_atoi_error(av[3], &err);
	philo->sleep = ft_atoi_error(av[4], &err);
	if (av[5])
		philo->meals = ft_atoi_error(av[5], &err);
	if (err)
	{
		free(philo);
		return (NULL);
	}
	else
		philo->meals = 0;
	return (philo);
}

int	main(int ac, char **av)
{
	struct timeval	tv;
	struct timeval	start;
	// int		i;
	t_philo	*philo;
	pthread_mutex_t	mutex;

	// i = 0;
	// pthread_t	philo[i];
	pthread_mutex_init(&mutex, NULL);
	if (ac < 5 || ac > 6)
	{
		invalid_argument_amount();
		return (1);
	}
	philo = init_philos(av);
	if (!philo)
		return (1);
	printf("Let's see what time it is.\n");
	if (gettimeofday(&tv, NULL) == -1)
		printf("An error occured, didn't catch the time.\n");
	else
	{
		start = tv;
		usleep(3000);
		if (gettimeofday(&tv, NULL) == -1)
			printf("An error occured, didn't catch the time.\n");
		else
			printf("It's been %ld milliseconds since this program started.\n", (tv.tv_usec - start.tv_usec) / 1000);
	}
	printf("atoi with nonnumbers: %d\n", atoi("3683209"));
	pthread_mutex_destroy(&mutex);
	return (0);
}

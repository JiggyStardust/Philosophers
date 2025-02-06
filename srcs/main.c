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
	if ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)) // can it contain whitespace?
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

int		assign_data_nums(char *av, t_data *data)
{
	int	err;

	err = 0;
	data->num_philos = ft_atoi_error(av[1], &err);
	if (err)
		return (0);
	data->time_dies = ft_atoi_error(av[2], &err);
	if (err)
		return (0);
	data->time_eat = ft_atoi_error(av[3], &err);
	if (err)
		return (0);
	data->time_sleeps = ft_atoi_error(av[4], &err);
	if (av[5])
		data->num_must_eat = ft_atoi_error(av[5], &err);
	else
		data->num_must_eat = -1; // or 0?
	if (err)
		return (0);
	else
		return (1);
}

void	free_destroy_forks(pthread_mutex_t *forks, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
		i--;
	}
	free(forks);
}

pthread_mutex_t	*assign_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!forks)
		return (NULL);
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0);
		{
			free_destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_data	*init_data(char **av)
{
	t_data	*data;
	int		err;

	err = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (!assign_data_nums(av, data))
	{
		free (data);
		return (NULL);
	}
	data->philo_died = false;
	data->forks = assign_forks(data);
	return (data);
}

t_philo	*init_philos(char **av)
{
	t_data	data;

	data = init_data(av);
	if (!data)
		return (NULL);
	
}

int	main(int ac, char **av)
{
	struct timeval	tv;
	struct timeval	start;
	// int		i;
	t_philo	*philo;

	// i = 0;
	// pthread_t	philo[i];
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
			printf("It's been %ld milliseconds since this program started.\n", (tv.tv_usec * - start.tv_usec) / 1000);
	}
	printf("atoi with nonnumbers: %d\n", atoi("3683209"));
	pthread_mutex_destroy(&mutex);
	return (0);
}

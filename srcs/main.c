#include "philosophers.h"

int	main(int ac, char **av)
{
	struct timeval	tv;
	struct timeval	start;

	if (ac < 5 || ac > 6)
	{
		ft_printf("Mandatory arguments (4 in total) are:\n");
		ft_printf("number_of_philosophers\n");
		ft_printf("time_to_die\n");
		ft_printf("time_to_eat\n");
		ft_printf("time_to_sleep\n");
		ft_printf("\nOptional:\n");
		ft_printf("number_of_times_each_philosopher_must_eat\n");
		return (1);
	}
	printf("Correct amount of args, first being %s.\n\b", av[1]);
	printf("Let's see what time it is.\n");
	if (gettimeofday(&tv, NULL) == -1)
		printf("An error occured, didn't catch the time.\n");
	else
	{
		start = tv;
		printf("It's been %d milliseconds since 1970.\n", tv.tv_usec / 1000);
		usleep(3000);
		if (gettimeofday(&tv, NULL) == -1)
			printf("An error occured, didn't catch the time.\n");
		else
			printf("It's been %d milliseconds since this program started.\n", (tv.tv_usec - start.tv_usec) / 1000);
	}
	return (0);
}
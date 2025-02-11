/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data_nums.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:13:58 by sniemela          #+#    #+#             */
/*   Updated: 2025/02/11 14:52:34 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		printf("Argument contained invalid characters.\n");
		return (0);
	}
	while (str[i])
	{
		if (str[i] < '0'|| str[i] > '9')
		{
			printf("Argument contained invalid characters.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_atoi_error(char *str, int *err)
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
		if (check > result)
			return (-1);
	}
	return ((int)result);
}
bool	arg_is_zero(char *s, int n)
{
	if (n == 0)
	{
		printf("%s should be over 0\n", s);
		return (true);
	}
	return (false);
}

int		assign_data_nums(char **av, t_data *data)
{
	int	err;

	err = 0;
	data->num_philos = ft_atoi_error(av[1], &err);
	if (err || arg_is_zero("number_of_philosophers", data->num_philos))
		return (0);
	data->time_dies = ft_atoi_error(av[2], &err);
	if (err || arg_is_zero("time_to_die", data->time_dies))
		return (0);
	data->time_eats = ft_atoi_error(av[3], &err);
	if (err)
		return (0);
	data->time_sleeps = ft_atoi_error(av[4], &err);
	if (av[5])
		data->num_must_eat = ft_atoi_error(av[5], &err);
	else
		data->num_must_eat = -1;
	if (err || arg_is_zero("minimum_meals", data->num_must_eat))
		return (0);
	data->start_time = get_time_ms();
	if (!data->start_time)
		return (0);
	else
		return (1);
}

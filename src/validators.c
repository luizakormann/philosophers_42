/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:24:54 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/13 20:41:50 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			validate_args(int argc, char **argv);
int			validate_argc(int argc);
long long	calc_check_interval(t_table *table);
int			check_all_ate(t_table *table);

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Invalid argument: %s\n", argv[i]);
				return (0);
			}
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Arguments must be positive integers\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid input. Correct usage:\n");
		printf("./bin/philo number_of_philos time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	else
		return (1);
}

long long	calc_check_interval(t_table *table)
{
	long long	cycle_based;

	cycle_based = table->time->time_to_sleep
		+ ((table->number_philos - 1) * table->time->time_to_eat);
	return (cycle_based);
}

int	check_all_ate(t_table *table)
{
	int	i;
	int	all_satisfied;

	if (table->must_eat == -1)
		return (0);
	all_satisfied = 1;
	i = 0;
	while (i < table->number_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meal_count < table->must_eat)
			all_satisfied = 0;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (all_satisfied);
}

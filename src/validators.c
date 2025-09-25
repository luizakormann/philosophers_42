/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:24:54 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:15:15 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int argc, char **argv);

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid input. Correct usage:\n");
		printf("./philo number_of_philos time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = 0;
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
		i++;
	}
	return (1);
}

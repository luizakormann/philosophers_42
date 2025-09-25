/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:22:26 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:37:14 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_time	*time;

	if (!validate_args(argc, argv))
		return (1);
	time = init_time(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
	if (!time)
		return (1);
	table = init_table(ft_atoi(argv[1]),
		(argc == 6) * ft_atoi(argv[5]) + !(argc == 6) * -1, time);
	if (!table)
		return (1);
	start_dinner(table);
	end_dinner(table);
	return (0);
}

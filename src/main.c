/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:22:26 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/07 15:48:18 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_time	*time;
	int		must_eat;

	if (!validate_args(argc, argv))
		return (1);
	must_eat = -1;
	if (argc == 6)
		must_eat = ft_atoi(argv[5]);
	time = init_time(ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
	if (!time)
		return (1);
	table = init_table(ft_atoi(argv[1]), must_eat, time);
	if (!table)
	{
		free(time);
		return (1);
	}
	start_dinner(table);
	end_dinner(table);
	return (0);
}

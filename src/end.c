/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:29:14 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:29:30 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_dinner(t_table *table);

void	end_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(table->death_mutex);
	pthread_mutex_destroy(table->log_mutex);

	free(table->forks);
	free(table->death_mutex);
	free(table->log_mutex);
	free(table->philos);
	free(table->time);
	free(table);
}

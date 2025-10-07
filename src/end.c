/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:29:14 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/07 15:58:05 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_dinner(t_table *table);
int		check_death(t_table *table);
void	set_death(t_table *table);

void	end_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
	i = 0;
	while (i < table->number_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->log_mutex);

	free(table->forks);
	free(table->philos);
	free(table->time);
	free(table);
}

int	check_death(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->death_mutex);
	dead = table->death_flag;
	pthread_mutex_unlock(&table->death_mutex);
	return (dead);
}

void	set_death(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->death_flag = 1;
	pthread_mutex_unlock(&table->death_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:29:14 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/13 20:43:04 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_death(t_table *table);
int		check_philo_death(t_philos *philo, t_table *table);
void	set_death(t_table *table);
void	end_dinner(t_table *table);


int	check_death(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->death_mutex);
	dead = table->death_flag;
	pthread_mutex_unlock(&table->death_mutex);
	return (dead);
}

int	check_philo_death(t_philos *philo, t_table *table)
{
	long long	time_since_last;
	long long	current_time;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_current_timestamp();
	time_since_last = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_last > table->time->time_to_die)
	{
		pthread_mutex_lock(&table->log_mutex);
		printf("%lld %d died\n",
			current_time - table->time->start_time, philo->id);
		pthread_mutex_unlock(&table->log_mutex);
		set_death(table);
		return (1);
	}
	return (0);
}

void	set_death(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->death_flag = 1;
	pthread_mutex_unlock(&table->death_mutex);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:22:20 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:56:33 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 	*philo_routine(void *arg);
void	eat(t_philos *philo);
void	snooze(t_philos *philo);
void	think(t_philos *philo);
void	*controller(void *arg);

void *philo_routine(void *arg)
{
	t_philos	*philo;
	t_table		*table;

	philo = (t_philos *)arg;
	table = philo->table;
	while (!table->death_flag)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		snooze(philo);
		think(philo);
	}
	return (NULL);
}

void	eat(t_philos *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(table->log_mutex);
	printf("%lld %d is eating\n",
		get_current_timestamp() - table->time->start_time,
		philo->id);
	pthread_mutex_unlock(table->log_mutex);
	philo->last_meal = get_current_timestamp();
	ms_sleep(table->time->time_to_eat);
	philo->meal_count++;
}

void	snooze(t_philos *philo)
{
	t_table	*table;

	table = philo->table;

	pthread_mutex_lock(table->log_mutex);
	printf("%lld %d is sleeping\n",
		get_current_timestamp() - table->time->start_time,
		philo->id);
	pthread_mutex_unlock(table->log_mutex);

	ms_sleep(table->time->time_to_sleep);
}

void	think(t_philos *philo)
{
	t_table	*table;

	table = philo->table;

	pthread_mutex_lock(table->log_mutex);
	printf("%lld %d is thinking\n",
		get_current_timestamp() - table->time->start_time,
		philo->id);
	pthread_mutex_unlock(table->log_mutex);
}

void	*controller(void *arg)
{
	t_table	*table;
	int		i;
	long long	time_since_last;

	table = (t_table *)arg;
	while (!table->death_flag)
	{
		i = 0;
		while (i < table->number_philos)
		{
			time_since_last = get_current_timestamp()
				- table->philos[i].last_meal;
			if (time_since_last > table->time->time_to_die)
			{
				pthread_mutex_lock(table->log_mutex);
				printf("Philosopher %d died\n", table->philos[i].id);
				pthread_mutex_unlock(table->log_mutex);
				table->death_flag = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

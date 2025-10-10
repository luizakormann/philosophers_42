/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:22:20 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/09 21:14:34 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg);
void	philo_eat(t_philos *philo);
void	philo_snooze(t_philos *philo);
void	philo_think(t_philos *philo);
void	*controller(void *arg);

void	*philo_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->table->number_philos == 1)
	{
		log_action(philo, "has taken a fork");
		ms_sleep(philo->table->time->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep((philo->table->time->time_to_eat * 1000) / 2);
	while (!check_death(philo->table))
	{
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_snooze(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	philo_eat(t_philos *philo)
{
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_current_timestamp();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ms_sleep(philo->table->time->time_to_eat);
}

void	philo_snooze(t_philos *philo)
{
	log_action(philo, "is sleeping");
	ms_sleep(philo->table->time->time_to_sleep);
}

void	philo_think(t_philos *philo)
{
	long long	time_to_think;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;

	log_action(philo, "is thinking");
	time_to_die = philo->table->time->time_to_die;
	time_to_eat = philo->table->time->time_to_eat;
	time_to_sleep = philo->table->time->time_to_sleep;
	time_to_think = (time_to_die - time_to_eat - time_to_sleep) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	if (time_to_think > 0)
		usleep(time_to_think * 1000);
}

void	*controller(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	usleep(1000);
	while (!check_death(table))
	{
		i = 0;
		while (i < table->number_philos)
		{
			if (check_philo_death(&table->philos[i], table))
				return (NULL);
			i++;
		}
		if (check_all_ate(table))
		{
			set_death(table);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

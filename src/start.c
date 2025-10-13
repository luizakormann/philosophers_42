/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 00:21:55 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/13 20:03:13 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time		*init_time(long long die, long long eat, long long sleep);
long long	get_current_timestamp(void);
t_table		*init_table(int n_philos, int must_eat, t_time *time);
t_philos	*create_philos(int n_philos, t_table *table);
void		start_dinner(t_table *table);

t_time	*init_time(long long die, long long eat, long long sleep)
{
	t_time	*time;

	time = malloc(sizeof(t_time));
	if (!time)
		return (NULL);
	time->start_time = get_current_timestamp();
	time->time_to_die = die;
	time->time_to_eat = eat;
	time->time_to_sleep = sleep;
	return (time);
}

long long	get_current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

t_table	*init_table(int n_philos, int must_eat, t_time *time)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_philos = n_philos;
	table->must_eat = must_eat;
	table->death_flag = 0;
	table->time = time;
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->log_mutex, NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!table->forks)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->philos = create_philos(n_philos, table);
	if (!table->philos)
		return (NULL);
	return (table);
}

t_philos	*create_philos(int n_philos, t_table *table)
{
	t_philos	*philos;
	int			i;

	philos = malloc(sizeof(t_philos) * n_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n_philos)
	{
		philos[i].id = i + 1;
		philos[i].meal_count = 0;
		philos[i].last_meal = table->time->start_time;
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % n_philos];
		philos[i].table = table;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	return (philos);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philos)
	{
		pthread_create(&table->philos[i].thread, NULL,
			&philo_routine, &table->philos[i]);
		i++;
	}
	pthread_create(&table->monitor, NULL, &controller, table);
}

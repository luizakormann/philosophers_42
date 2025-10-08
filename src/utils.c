/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiza <luiza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:34:30 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/07 17:59:58 by luiza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(const char *nptr);
void	ms_sleep(long long ms);
void	log_action(t_philos *philo, char *action);
void	take_forks(t_philos *philo);
void	drop_forks(t_philos *philo);


int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		sig;

	i = 0;
	res = 0;
	sig = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sig = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sig);
}

void	ms_sleep(long long ms)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = get_current_timestamp();
	while (1)
	{
		elapsed = get_current_timestamp() - start;
		remaining = ms - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 1)
			usleep((remaining / 2) * 1000);
		else
			usleep(100);
	}
}
/* PAREI AQUI */
void	log_action(t_philos *philo, char *action)
{
	t_table		*table;
	long long	timestamp;
	int			dead;

	table = philo->table;
	pthread_mutex_lock(&table->death_mutex);
	dead = table->death_flag;
	pthread_mutex_unlock(&table->death_mutex);

	if (dead)
		return;

	pthread_mutex_lock(&table->log_mutex);
	timestamp = get_current_timestamp() - table->time->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&table->log_mutex);
}

void	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_action(philo, "has taken a fork");
	}
}

void	drop_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

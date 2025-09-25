/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:36:18 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:56:59 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philos	t_philos;
typedef struct s_table	t_table;
typedef struct s_time	t_time;


typedef struct s_philos
{
	int				id;
	long long		last_meal;
	int				meal_count;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;

}	t_philos;

typedef struct s_table
{
	int				number_philos;
	int				must_eat;
	int				death_flag;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*forks;
	t_philos		*philos;
	t_time			*time;
}	t_table;

typedef struct s_time
{
	long long	start_time;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;

}	t_time;

//start
t_philos	*create_philos(int n_philos, t_table *table);
t_table		*init_table(int n_philos, int must_eat, t_time *time);
t_time		*init_time(long long die, long long eat, long long sleep);
void		start_dinner(t_table *table);
long long	get_current_timestamp(void);

//validate
int			validate_args(int argc, char **argv);

//routines
void		*philo_routine(void *arg);
void		eat(t_philos *philo);
void		snooze(t_philos *philo);
void		think(t_philos *philo);
void		*controller(void *arg);

//end
void		end_dinner(t_table *table);

//utils
int			ft_atoi(const char *nptr);
void		ms_sleep(long long ms);


#endif

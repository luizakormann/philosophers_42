/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:36:18 by lukorman          #+#    #+#             */
/*   Updated: 2025/10/13 20:45:21 by lukorman         ###   ########.fr       */
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
	pthread_mutex_t	meal_mutex;
	t_table			*table;

}	t_philos;

typedef struct s_table
{
	int				number_philos;
	int				must_eat;
	int				death_flag;
	int				all_ate;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
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
t_time		*init_time(long long die, long long eat, long long sleep);
long long	get_current_timestamp(void);
t_table		*init_table(int n_philos, int must_eat, t_time *time);
t_philos	*create_philos(int n_philos, t_table *table);
void		start_dinner(t_table *table);

//validators
int			validate_args(int argc, char **argv);
int			validate_argc(int argc);
long long	calc_check_interval(t_table *table);
int			check_all_ate(t_table *table);

//routines
void		*philo_routine(void *arg);
void		philo_eat(t_philos *philo);
void		philo_snooze(t_philos *philo);
void		philo_think(t_philos *philo);
void		*controller(void *arg);

//end
int			check_death(t_table *table);
int			check_philo_death(t_philos *philo, t_table *table);
void		set_death(t_table *table);
void		end_dinner(t_table *table);

//utils
int			ft_atoi(const char *nptr);
void		ms_sleep(long long ms);
void		log_action(t_philos *philo, char *action);
int			take_forks(t_philos *philo);
void		drop_forks(t_philos *philo);

#endif

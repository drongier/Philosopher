/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:09:38 by drongier          #+#    #+#             */
/*   Updated: 2024/11/29 17:31:49 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_table
{
	int				nb_philos;
	int				nb_meal;
	int				stop;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	pthread_t		spy_philo;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	struct s_philo	**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	int					times_ate;
	unsigned int		left_fork;
	unsigned int		right_fork;
	pthread_mutex_t		meal_lock;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

int				arg_is_ok(char **av);
int				ft_isdigit(int c);
t_table			*init_table(int ac, char **av);
t_philo			**init_philo(t_table *table);
int				init_global_mutexes(t_table *table);
void			*philosopher(void *data);
time_t			get_time(void);
void			philo_sleep(t_table *table, time_t time_to_sleep);
void			write_status(t_philo *philo, char *str, int flag_spy);
void			*spy_philo(void *data);
int				check_prog(t_table *table);
void			*end_prog(t_table *table);
void			destroy_mutexes(t_table *table);
void			exit_error(int i);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:22:43 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:37:20 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0

typedef struct s_philo
{
	int					id;
	int					meal_count;
	size_t					last_meal;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_nbr;
	size_t				start_time;
	int				philo_dead;
	int				all_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		write_lock;

}	t_table;

void	ft_sleep_eat(t_table *tab, size_t time);
void	print_message(t_philo *philo, char *message);
void	init_forks(t_table *table, int philo_nbr);
void	init_prog(t_table *table);
void	exit_error(int i);
void	*philo_routine(void *arg);
int		arg_is_ok(char **av);
size_t		get_time(void);
void		check_dead_loop(t_table *tab);
int		init_philos(t_table *table);
int		init_struct(t_table *table, char **av);
void	check_dead_loop(t_table *tab);

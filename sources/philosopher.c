/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:08:13 by drongier          #+#    #+#             */
/*   Updated: 2024/11/29 17:33:46 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork]);
	write_status(philo, "has taken fork", 0);
	pthread_mutex_lock(&philo->table->fork_locks[philo->right_fork]);
	write_status(philo, "has taken fork", 0);
	write_status(philo, "is eating", 0);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	philo_sleep(philo->table, philo->table->time_to_eat);
	if (check_prog(philo->table) == 0)
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->times_ate = philo->times_ate + 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	write_status(philo, "is sleeping", 0);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->right_fork]);
}

static void	think_routine(t_philo *philo)
{
	time_t	t_to_think;
	time_t	t_b_die;

	pthread_mutex_lock(&philo->meal_lock);
	t_b_die = (philo->table->time_to_die - ((get_time() - philo->last_meal)));
	t_to_think = ((t_b_die - philo->table->time_to_eat) / 2);
	pthread_mutex_unlock(&philo->meal_lock);
	write_status(philo, "is thinking", 0);
	philo_sleep(philo->table, t_to_think);
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->left_fork]);
	write_status(philo, "has taken fork", 0);
	philo_sleep(philo->table, philo->table->time_to_die);
	write_status(philo, "died", 0);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->left_fork]);
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	while (check_prog(philo->table) == 0)
	{
		eat_sleep_routine(philo);
		philo_sleep(philo->table, philo->table->time_to_sleep);
		think_routine(philo);
	}
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->nb_meal == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->table->nb_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	philo_routine(philo);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:12:36 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:17:02 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->table->philo_dead == 1)
		return (pthread_mutex_unlock(&philo->dead_lock), 1);
	pthread_mutex_unlock(&philo->dead_lock);
	return (0);
}

void	eat_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken fork", philo, philo->id);
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meal_count++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_sleep_eat(table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_dead_loop(philo))
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		eat_routine(philo);
		ft_sleep_eat(philo->time_to_sleep);
		print_message("is spleeping", philo, philo->id);
		print_message("is thinking", philo, philo->id);
	}
	return (NULL);
}

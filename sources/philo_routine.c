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

void	kill_one_philo(t_table *table, t_philo *philo)
{
	{
		ft_sleep_eat(table, table->time_to_eat);
		print_message(philo, "died");
		table->philo_dead = 1;
		pthread_mutex_unlock(&philo->table->forks_lock[philo->fork[0]]);
	}
}

void	eat_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->table->forks_lock[philo->fork[0]]);
	print_message(philo, "has taken fork");
	if (table->philo_nbr == 1)
	{
		kill_one_philo(table, philo);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks_lock[philo->fork[1]]);
	print_message(philo, "has taken fork");
	pthread_mutex_lock(&philo->time_meal);
	philo->meal_count++;
	print_message(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_meal);
	ft_sleep_eat(table, table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->fork[1]]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->table;
	printf("coucou\n");
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->philo_dead && !tab->all_eat)
	{
		printf("coucou\n");
		eat_routine(philo);
		print_message(philo, "is sleeping");
		ft_sleep_eat(tab, tab->time_to_eat);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:11:45 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:12:07 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philo)
		return (exit_error(1), FALSE);
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meal_count = 0;
		table->philo[i].table = table;
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_init(&table->philo[i].time_meal, NULL);
		table->philo[i].left_fork = &table->forks[i];
		if (i == 0)
			table->philo[i].right_fork = &table->forks[table->philo_nbr - 1];
		else
			table->philo[i].right_fork = &table->forks[i - 1];
		i++;
	}
	return (TRUE);
}

int	init_struct(t_table *table, char **av)
{
	table->philo_nbr = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->philo_dead = 0;
	table->all_eat = 0;
	if (av[5])
		table->meal_nbr = atoi(av[5]);
	else
		table->meal_nbr = -1;
	return (TRUE);
}

void	init_forks(t_table *table, int philo_nbr)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	while (i < philo_nbr)
	{
		pthread_mutex_init(&table->philo[i].fork, NULL);
		i++;
	}
}

void	init_prog(t_table *table)
{
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}

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

static void assigne_fork(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->philo_nbr;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->philo_nbr;
		philo->fork[1] = philo->id;
	}
}

t_philo	**init_philos(t_table *table)
{
	t_philo	**philo;
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philo)
		return (NULL);
	while (i < table->philo_nbr)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
            return (NULL);
		philo[i]->id = i + 1;
		philo[i]->meal_count = 0;
		philo[i]->table = table;
		philo[i]->last_meal = table->start_time;
		pthread_mutex_init(&philo[i]->time_meal, NULL);
		assigne_fork(philo[i]);
		i++;
	}
	return (philo);
}

void	init_struct(t_table *table, char **av)
{
	table = malloc(sizeof(t_table) * 1);
	table->philo_nbr = atoi(av[1]);
	printf("%i\n", table->philo_nbr);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->philo_dead = 0;
	table->all_eat = 0;
	if (av[5])
		table->meal_nbr = atoi(av[5]);
	else
		table->meal_nbr = -1;
}

static pthread_mutex_t	*init_forks(t_table *table)
{

	pthread_mutex_t	*forks;
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&forks[i], 0);
		i++;
	}
	return (forks);
}

void	init_prog(t_table *table)
{
	table->forks_lock = init_forks(table);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}

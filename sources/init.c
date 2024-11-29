/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:54:12 by drongier          #+#    #+#             */
/*   Updated: 2024/11/29 17:32:07 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
	{
		if (table != NULL)
			end_prog(table);
		return (NULL);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			if (table != NULL)
				end_prog(table);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	init_philo_info(t_philo *philo, t_table *table, int i)
{
	philo->table = table;
	philo->id = i;
	philo->times_ate = 0;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % table->nb_philos;
	if (i % 2)
	{
		philo->left_fork = (i + 1) % table->nb_philos;
		philo->right_fork = i;
	}
}

t_philo	**init_philo(t_table *table)
{
	t_philo			**philos;
	int				i;

	philos = malloc(sizeof(t_philo *) * table->nb_philos);
	if (!philos)
		return (end_prog(table), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			end_prog(table);
			return (NULL);
		}
		if (pthread_mutex_init(&philos[i]->meal_lock, NULL) != 0)
		{
			end_prog(table);
			return (NULL);
		}
		init_philo_info(philos[i], table, i);
		i++;
	}
	return (philos);
}

int	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (0);
	if (pthread_mutex_init(&table->end_lock, 0) != 0)
	{
		end_prog(table);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
	{
		end_prog(table);
		return (EXIT_FAILURE);
	}
	return (1);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
	{
		end_prog(table);
		return (NULL);
	}
	table->nb_philos = atoi(av[1]);
	table->time_to_die = atoi(av[2]);
	table->time_to_eat = atoi(av[3]);
	table->time_to_sleep = atoi(av[4]);
	table->nb_meal = -1;
	if (ac - 1 == 5)
		table->nb_meal = atoi(av[5]);
	table->stop = 0;
	return (table);
}

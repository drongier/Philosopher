/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:24:23 by drongier          #+#    #+#             */
/*   Updated: 2024/10/24 15:45:44 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_prog(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->philo->dead_lock);
	pthread_mutex_destroy(&table->philo->write_lock);
	pthread_mutex_destroy(&table->philo->meal_lock);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

int	create_thread(t_table *table)
{
	int			i;
	pthread_t	spy;

	i = 0;
	table->start_time = get_time();
	if (pthread_create(&spy, NULL, &spy_philos, &table->philo[i]) != 0)
		end_prog(table);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, &philo_routine, (void *)&table->philo[i]))
			return (exit_error(1), FALSE);
		i++;
	}
	i = 0;
	if (pthread_join(spy, NULL) != 0)
		end_prog(table);
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
	return (TRUE);
}

void	free_philo(t_table *table)
{
	free(table->philo);
	free(table->forks);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (exit_error(3), FALSE);
	if (arg_is_ok(av))
		init_struct(&table, av);
	init_forks(&table, table.philo_nbr);
	init_philos(&table);
	init_prog(&table);
	create_thread(&table);
	end_prog(&table);
	free_philo(&table);
}

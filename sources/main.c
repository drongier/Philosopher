/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:24:23 by drongier          #+#    #+#             */
/*   Updated: 2024/11/20 18:49:49 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_prog(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philo[i]->thread_id, NULL);
		i++;
	}
	if (table->philo_nbr > 1)
		pthread_join(table->check_dead_loop, NULL);
	i = 0;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->write_lock);
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philo[i]->time_meal);
		pthread_mutex_destroy(&table->forks_lock[i]);
		i++;
	}
	free(table->philo);
}

void	start_program(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i]->thread_id, NULL, &philo_routine, &table->philo[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(table->philo);
			exit(1);
		}
		pthread_mutex_lock(&table->philo[i]->time_meal);
		table->philo[i]->last_meal = table->start_time;
		pthread_mutex_unlock(&table->philo[i]->time_meal);
	}
	if (table->philo_nbr > 1)
	{
		pthread_create(&table->check_dead_loop, NULL, &check_dead_loop, table);
	}
}

int	main(int ac, char **av)
{
	t_table		*table;

	if (ac < 5 || ac > 6)
		return (exit_error(3), FALSE);
	if (arg_is_ok(av))
	{
		table = malloc(sizeof(t_table) * 1);
		init_struct(table, av);
		printf("%i\n", table->philo_nbr);
		table->philo = init_philos(table);
		init_prog(table);
		start_program(table);
		end_prog(table);
	}
	else
		return (0);
}

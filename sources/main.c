/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:06:08 by drongier          #+#    #+#             */
/*   Updated: 2024/12/02 11:17:20 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_prog(t_table	*table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->spy_philo, NULL);
	destroy_mutexes(table);
	end_prog(table);
}

static int	start_prog(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, \
					&philosopher, table->philos[i]) != 0)
		{
			if (table != NULL)
				end_prog(table);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->spy_philo, NULL, &spy_philo, table) != 0)
		{
			if (table != NULL)
				end_prog(table);
			return (EXIT_FAILURE);
		}
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
	{
		exit_error(3);
		return (EXIT_FAILURE);
	}
	if (arg_is_ok(av))
	{
		table = init_table(ac, av);
		if (!table)
			return (EXIT_FAILURE);
		table->philos = init_philo(table);
		if (!table->philos)
			return (EXIT_FAILURE);
		if (!init_mutexes(table))
			return (EXIT_FAILURE);
		table->start_time = get_time();
		if (!start_prog(table))
			return (EXIT_FAILURE);
		stop_prog(table);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

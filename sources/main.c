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

void	end_prog(t_table *table, pthread_t	*id)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(id[i], NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->write_lock);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	free(table->philo);
	free(table->forks);
	free(id);
}

int	main(int ac, char **av)
{
	int 		i;
	t_table		table;
	pthread_t	*id;

	if (ac < 5 || ac > 6)
		return (exit_error(3), FALSE);
	
	if (arg_is_ok(av))
	{
		init_struct(&table, av);
		init_forks(&table, table.philo_nbr);
		init_philos(&table);
		init_prog(&table);
	}
	table.start_time = get_time();
	i = -1;
	id = (pthread_t *)malloc(table.philo_nbr * sizeof(pthread_t));
	printf("philo dead = %i\n", table.philo_dead);
	while (++i < table.philo_nbr)
	{
		if (pthread_create(&id[i], NULL, &philo_routine, &table.philo[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(table.philo);
			free(id);
			return (1);
		}
		pthread_mutex_lock(&table.dead_lock);
		table.philo[i].last_meal = table.start_time;
		pthread_mutex_unlock(&table.dead_lock);
	}
	printf("philo dead = %i\n", table.philo_dead);
	check_dead_loop(&table);
	end_prog(&table, id);
	return (0);
}

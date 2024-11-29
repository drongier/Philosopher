/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:53:57 by drongier          #+#    #+#             */
/*   Updated: 2024/11/29 16:59:30 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*end_prog(t_table *table)
{
	int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

void	exit_error(int i)
{
	if (i == 1)
		printf("Error: Arg is not a number !\n");
	else if (i == 2)
		printf("Error: INT MAX or INT MIN !\n");
	else if (i == 3)
		printf("Error: pls use ./philo xxx xxx xxx xxx [x]\n");
	else if (i == 4)
		printf("Error: Too many philosophers !\n");
	else if (i == 6)
		printf("Error mutex !\n");
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

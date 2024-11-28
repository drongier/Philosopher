/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spy_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:08:20 by drongier          #+#    #+#             */
/*   Updated: 2024/11/28 19:18:58 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_prog(t_table *table)
{
	int	stop_prog;

	stop_prog = 0;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == 1)
		stop_prog = 1;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (stop_prog);
}

static int	check_dead_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->sim_stop_lock);
		philo->table->sim_stop = 1;
		pthread_mutex_unlock(&philo->table->sim_stop_lock);
		write_status(philo, "died", 1);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	return (0);
}

static int	end_condition_reached(t_table *table)
{
	unsigned int	i;
	int				all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (check_dead_philo(table->philos[i]))
			return (1);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate
				< (unsigned int)table->must_eat_count)
				all_ate_enough = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == 1)
	{
		pthread_mutex_lock(&table->sim_stop_lock);
		table->sim_stop = 1;
		pthread_mutex_unlock(&table->sim_stop_lock);
		return (1);
	}
	return (0);
}

void	*spy_philo(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = 0;
	pthread_mutex_unlock(&table->sim_stop_lock);
	usleep(200);
	while (1 || table->must_eat_count == 0)
	{
		if (end_condition_reached(table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spy_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:08:20 by drongier          #+#    #+#             */
/*   Updated: 2024/12/02 10:59:05 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_prog(t_table *table)
{
	int	stop_prog;

	stop_prog = 0;
	pthread_mutex_lock(&table->end_lock);
	if (table->stop == 1)
		stop_prog = 1;
	pthread_mutex_unlock(&table->end_lock);
	return (stop_prog);
}

static int	check_dead_philo(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_lock);
		philo->table->stop = 1;
		pthread_mutex_unlock(&philo->table->end_lock);
		write_status(philo, "died", 1);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	return (0);
}

static int	check_condition(t_table *table)
{
	int				i;
	int				all_meal_eat;

	all_meal_eat = 1;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_lock);
		if (check_dead_philo(table->philos[i]))
			return (1);
		if (table->nb_meal != -1)
			if (table->philos[i]->times_ate < table->nb_meal)
				all_meal_eat = 0;
		pthread_mutex_unlock(&table->philos[i]->meal_lock);
		i++;
	}
	if (table->nb_meal != -1 && all_meal_eat == 1)
	{
		pthread_mutex_lock(&table->end_lock);
		table->stop = 1;
		pthread_mutex_unlock(&table->end_lock);
		return (1);
	}
	return (0);
}

void	*spy_philo(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	pthread_mutex_lock(&table->end_lock);
	table->stop = 0;
	pthread_mutex_unlock(&table->end_lock);
	usleep(200);
	while (1 || table->nb_meal == 0)
	{
		if (check_condition(table) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

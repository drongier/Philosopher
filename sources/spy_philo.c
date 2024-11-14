/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spy_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:17:27 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:20:48 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int philo_dead(t_philo *philo, int time_to_die)
{
    int time_diff;
    
    pthread_mutex_lock(&philo->meal_lock);
    time_diff = get_time() - philo->last_meal;
    pthread_mutex_unlock(&philo->meal_lock);
    
    if (time_diff >= time_to_die)
        return (1);
    return (0);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->philo_nbr)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die))
		{
			print_message("died", &philo[i], philo[i].id);
			pthread_mutex_lock(&philo->table->dead_lock);
			philo->table->philo_dead = 1;
			pthread_mutex_unlock(&philo->table->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo->table->meal_nbr == -1)
		return (0);
	while (i < philo->table->philo_nbr)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].meal_count >= philo->table->meal_nbr)
			finished_eating++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	if (finished_eating == philo->table->philo_nbr)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		philo->table->philo_dead = 1;
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (1);
	}
	return (0);
}

void	*spy_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_if_all_ate(philo) == 1 || check_if_dead(philo) == 1)
			break ;
	}
	return (arg);
}

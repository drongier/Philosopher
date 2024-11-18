/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:12:36 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:17:02 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_dead_loop(t_table *tab)
{
	int	i;

	while (!tab->all_eat)
	{
		i = -1;
		while (!tab->philo_dead && ++i < tab->philo_nbr)
		{
			printf("time %zu\n", get_time());
			printf("last meal %u\n", tab->philo[i].last_meal);
			printf("time to eat %zu\n", (size_t)tab->time_to_eat);
			pthread_mutex_lock(&tab->dead_lock);
			if (get_time() - tab->philo[i].last_meal > (size_t)tab->time_to_eat)
			{
				afficher_message(&tab->philo[i], "is died");
				tab->philo_dead = 0;
			}
			pthread_mutex_unlock(&tab->dead_lock);
			usleep(100);
		}
		if (tab->philo_dead)
			break ;
		i = 0;
		while (tab->meal_nbr != -1 && i < tab->philo_nbr
			&& tab->philo[i].meal_count >= tab->meal_nbr)
			i++;
		if (i == tab->philo_nbr)
			tab->all_eat = 1;
	}
}

void	eat_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	afficher_message(philo, "has taken fork");
	pthread_mutex_lock(philo->right_fork);
	afficher_message(philo, "has taken fork");
	pthread_mutex_lock(&table->dead_lock);
	philo->meal_count++;
	afficher_message(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&table->dead_lock);
	ft_sleep_eat(table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->philo_dead && !tab->all_eat)
	{
		eat_routine(philo);
		afficher_message(philo, "is sleeping");
		ft_sleep_eat(tab->time_to_eat);
		afficher_message(philo, "is thinking");
	}
	return (NULL);
}

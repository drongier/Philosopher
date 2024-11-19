/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:21:10 by drongier          #+#    #+#             */
/*   Updated: 2024/10/25 14:22:01 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_error(int i)
{
	if (i == 1)
	{
		printf("Error: Arg is not a number !\n");
		exit(1);
	}
	else if (i == 2)
	{
		printf("Error: INT MAX or INT MIN !\n");
		exit(1);
	}
	else if (i == 3)
		printf("Error: pls use ./philo xxx xxx xxx xxx [x]\n");
}

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep_eat(t_table *tab, size_t time)
{
	size_t	t;

	t = get_time();
	while (!(tab->philo_dead))
	{
		if (get_time() - t >= time)
			break ;
		usleep(100);
	}
}

void	print_message(t_philo *philo, char *message)
{
	size_t	t;

	t = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_lock);
	if (!philo->table->philo_dead && !philo->table->all_eat)
	{
		printf("%ld ", t);
		printf(" %d ", philo->id);
		printf("%s", message);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}

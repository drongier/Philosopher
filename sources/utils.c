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
		printf("Error: Arg is not a number !\n");
	else if (i == 2)
		printf("Error: INT MAX or INT MIN !\n");
	else if (i == 3)
		printf("Error: pls use ./philo xxx xxx xxx xxx [x]\n");
}

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep_eat(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->write_lock);
	time = get_time() - philo->table->start_time;
	if (!check_dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->table->write_lock);
}

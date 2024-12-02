/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:07:26 by drongier          #+#    #+#             */
/*   Updated: 2024/11/29 17:18:36 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time() - philo->table->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, char *str, int flag_spy)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_prog(philo->table) == 1 && flag_spy == 0)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	print_status(philo, str);
	pthread_mutex_unlock(&philo->table->write_lock);
}

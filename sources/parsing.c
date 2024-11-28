/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drongier <drongier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:08:08 by drongier          #+#    #+#             */
/*   Updated: 2024/11/28 19:23:55 by drongier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	arg_is_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (exit_error(1), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	arg_min_max(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((ft_atol(av[i]) >= INT_MAX) || (ft_atol(av[i]) <= INT_MIN))
			return (exit_error(2), 0);
		i++;
	}
	return (1);
}

int	nb_philo_ok(char **av)
{
	if (ft_atol(av[1]) > 200)
		return (exit_error(4), 0);
	else 
		return (1);
}

int	arg_is_ok(char **av)
{
	if (arg_min_max(av) && arg_is_num(av) && nb_philo_ok(av))
		return (1);
	else
		return (0);
}

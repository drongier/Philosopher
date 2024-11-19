#include "../includes/philo.h"

void	check_dead_loop(t_table *tab)
{
	int	i;

	while (!tab->all_eat)
	{
		i = -1;
		while (!tab->philo_dead && ++i < tab->philo_nbr)
		{
			pthread_mutex_lock(&tab->dead_lock);
			if (get_time() - tab->philo[i].last_meal > (size_t)tab->time_to_die)
			{
				print_message(&tab->philo[i], "is died");
				tab->philo_dead = 1;
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
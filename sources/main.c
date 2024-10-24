#include "../includes/philo.h"

void    end_prog(t_table *table)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&table->philo->dead_lock);
    pthread_mutex_destroy(&table->philo->write_lock);
    pthread_mutex_destroy(&table->philo->meal_lock);
    while (i < table->philo_nbr)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
}

int init_philos(t_table *table)
{
    int i;

    i = 0;
    table->philo = malloc(sizeof(t_philo) * table->philo_nbr);
    if (!table->philo)
        return (exit_error(1), FALSE);
    while (i < table->philo_nbr)
    {
        table->philo[i].id = i + 1;
        table->philo[i].time_to_die = table->time_to_die;
        table->philo[i].time_to_eat = table->time_to_eat;
        table->philo[i].time_to_sleep = table->time_to_sleep;
        table->philo[i].meal_count = 0;
        table->philo[i].last_meal = get_time();
        table->philo[i].table = table;
        table->philo[i].left_fork = &table->forks[i];
        if (i == 0)
            table->philo[i].right_fork = &table->forks[table->philo_nbr - 1];
        else
            table->philo[i].right_fork = &table->forks[i - 1];
        printf("Philosopher %d: Left fork at %p, Right fork at %p\n", 
               table->philo[i].id, 
               (void *)table->philo[i].left_fork, 
               (void *)table->philo[i].right_fork);
        i++;
    }
    return (TRUE);
}

int    create_thread(t_table *table)
{
    int i;
    pthread_t spy;

    i = 0;
    table->start_time = get_time();
    if (pthread_create(&spy, NULL, &spy_philos, &table->philo[i]) != 0)
	 	end_prog(table);
    while (i < table->philo_nbr)
    {
        if (pthread_create(&table->philo[i].thread_id, NULL, &philo_routine, (void *)&table->philo[i]))
            return (exit_error(1), FALSE);
        i++;
    }
    i = 0;
    if (pthread_join(spy, NULL) != 0)
        end_prog(table);
    while (i < table->philo_nbr)
    {
        pthread_join(table->philo[i].thread_id, NULL);
        i++;
    }
    return (TRUE);
}

int init_struct(t_table *table, char **av)
{
    table->philo_nbr = atoi(av[1]);
    table->time_to_die = atoi(av[2]);
    table->time_to_eat = atoi(av[3]);
    table->time_to_sleep = atoi(av[4]);
    table->philo_dead = 0;
    if (av[5])
        table->meal_nbr = atoi(av[5]);
    else
        table->meal_nbr = -1;
    printf("init_struct: Initialized with %d philosophers\n", table->philo_nbr);
    printf("init_struct: Initialized with %d time_to_die\n", table->time_to_die);
    return (TRUE);
}

void    init_forks(t_table *table, int philo_nbr)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
    while (i < philo_nbr)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
}

void    init_prog(t_table *table)
{
    pthread_mutex_init(&table->philo->dead_lock, NULL);
    pthread_mutex_init(&table->philo->write_lock, NULL);
    pthread_mutex_init(&table->philo->meal_lock, NULL);   
}

void    free_philo(t_table *table)
{
    free(table->philo);
    free(table->forks);
}

int main(int ac, char **av)
{
    t_table table;

    if (ac < 5 || ac > 6)
        return (exit_error(3), FALSE);
    if (arg_is_ok(av))
        init_struct(&table, av);
    init_forks(&table, table.philo_nbr);
    init_philos(&table);
    init_prog(&table);
    create_thread(&table);
    end_prog(&table);
    free_philo(&table);
}
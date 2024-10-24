#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct  s_philo
{
    int                 id;
    int                 time_to_die;
    int                 time_to_eat;
    int                 time_to_sleep;
    int                 meal_count;
    int                 last_meal;
    pthread_t           thread_id;
    pthread_mutex_t     meal_lock;
    pthread_mutex_t     dead_lock;
    pthread_mutex_t     write_lock;
    struct  s_table     *table;
    pthread_mutex_t     *left_fork;
    pthread_mutex_t     *right_fork;

} t_philo;

typedef struct s_table
{
    int    philo_nbr;
    int    time_to_die;
    int    time_to_eat;
    int    time_to_sleep;
    int    meal_nbr;
    int    start_time;
    int    philo_dead;
    t_philo           *philo;
    pthread_mutex_t   *forks;

} t_table;

void    exit_error(int i);
int     arg_is_ok(char **av);
void    *philo_routine(void *arg);
int     get_time(void);
void    ft_sleep_eat(int time);
void	*spy_philos(void *arg);
void	print_message(char *str, t_philo *philo, int id);
int check_dead_loop(t_philo *philo);


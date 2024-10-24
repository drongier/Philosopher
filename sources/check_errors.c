#include "../includes/philo.h"

int arg_is_num(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
                return (exit_error(1), FALSE);
            j++;
        }
        i++;
    }
    return (TRUE);
    
}

int arg_min_max(char **av) // ATTENTION ATOL TO MODIFI
{
    int i;

    i = 0;
    while (av[i])
    {
        if ((atol(av[i]) >= INT_MAX) || (atol(av[i]) <= INT_MIN))
            return (exit_error(2), FALSE);
        i++;
    }
    return (TRUE);
}

int arg_is_ok(char **av)
{
    if (arg_min_max(av) && arg_is_num(av))
            return (TRUE);
    else
        return (FALSE);
}

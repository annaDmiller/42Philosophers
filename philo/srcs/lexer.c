#include "../includes/philo_header.h"

int check_intro_values(t_all *all, int argc)
{
    if (all->num_philos <= 0 || all->to_die <= 0
        || all->to_eat <= 0 || all->to_sleep <= 0)
        return (write_err("Incorrect input values. Please, double check them"),
            -1);
    if (argc == 6 && all->num_eat < 0)
        return (write_err("Incorrect input values. Please, double check them"),
            -1);
    return (0);
}

int validate_args(int argc, char **argv)
{
    int ind_arg;
    int ind_car;

    ind_arg = 0;
    while (++ind_arg < argc)
    {
        ind_car = 0;
        while (argv[ind_arg][ind_car])
        {
            if (!ft_isdigit(argv[ind_arg][ind_car]))
                return (0);
            ind_car++;
        }
    }
    return (1);
}
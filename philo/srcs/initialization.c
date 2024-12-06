#include "../includes/philo_header.h"

static pthread_mutex_t *init_forks(t_all *all);
static t_philo  *init_philos(t_all *all);

t_all   *init_all(int argc, char **argv)
{
    t_all   *all;

    all = (t_all *) malloc(sizeof(t_all));
    if (!all)
        return (write_err("Malloc error"), NULL);
    all->num_philos = ft_atol(argv[1]);
    all->is_dead = 0;
    if (pthread_mutex_init(&(all->mess), NULL) == -1)
        return (write_err("Mutex init error"), free(all), NULL);
    all->to_die = ft_atol(argv[2]);
    all->to_eat = ft_atol(argv[3]);
    all->to_sleep = ft_atol(argv[4]);
    if (argc == 6)
        all->num_eat = ft_atol(argv[5]);
    else
        all->num_eat = -1;
    all->forks = NULL;
    all->philos = NULL;
    return (all);
}

int init_forks_and_philos(t_all *all)
{
    all->forks = init_forks(all);
    if (!all->forks)
        return (write_err("Malloc error"), -1);
    all->philos = init_philos(all);
    if (!all->philos)
        return (write_err("Malloc error"), -1);
    return (0);
}

static pthread_mutex_t *init_forks(t_all *all)
{
    pthread_mutex_t *ret;
    long            ind;

    ret = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * all->num_philos);
    if (!ret)
        return (NULL);
    ind = -1;
    while (++ind < all->num_philos)
    {
        if (pthread_mutex_init(&(ret[ind]), NULL) == -1)
            return (write_err("Mutex init error"), mut_destroy_err(all, ind), NULL);
    }
    return (ret);
}

static t_philo  *init_philos(t_all *all)
{
    t_philo *ret_arr;
    long    ind;

    ret_arr = (t_philo *) malloc(sizeof(t_philo));
    if (!ret_arr)
        return (NULL);
    ind = -1;
    while (++ind < all->num_philos)
    {
        ret_arr->eat_times = 0;
        ret_arr->state = '0';
        ret_arr->num_ph = ind;
        ret_arr->tz = NULL;
        ret_arr->tv = NULL;
        //if (gettimeofday(ret_arr->tv, ret_arr->tz) == -1)
    }
    return (ret_arr);
}
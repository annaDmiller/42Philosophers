#include "../../includes/philo_header.h"

void    free_all(t_all *all, int destroy_forks, int detach_th)
{
    long    ind;

    if (all->forks)
    {
        if (destroy_forks)
            mut_destroy(all->forks, all->num_philos);
        free(all->forks);
    }
    if (all->philos)
    {
        if (detach_th)
            detach_thread(all, all->num_philos);
        free(all->philos);
    }
    pthread_mutex_destroy(&((all->fin).mut));
    pthread_mutex_destroy(&(all->mess));
    free(all);
}

void    mut_destroy(pthread_mutex_t *forks, long stop_at)
{
    long    ind;

    ind = 0;
    while (ind < stop_at)
    {
        pthread_mutex_destroy(&(forks[ind]));
        ind++;
    }
    return ;
}

void    detach_thread(t_all *all, long stop_at)
{
    long    ind;

    ind = 0;
    while (ind < stop_at)
    {
        pthread_detach((all->philos[ind]).thread);
        ind++;
    }
    return ;
}
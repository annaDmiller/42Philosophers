#include "../includes/philo_bonus_header.h"

static sem_t    *init_forks(t_all *all);

int init_forks_and_philos(t_all *all)
{
    all->forks = init_forks(all);
    if (!all->forks)
        return (-1);
    all->philo = init_philos(all);
    if (!all->philo)
        return (-1);
    return (0);
}

static sem_t    *init_forks(t_all *all)
{
    sem_t   *ret;

    ret = sem_open(FORKS, O_CREAT | O_EXCL, 0644, all->num_philos);
    if (ret == SEM_FAILED)
        return (write_err("Open sema failed"), NULL);
    return (ret);
}
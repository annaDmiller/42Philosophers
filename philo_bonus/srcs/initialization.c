#include "../includes/philo_bonus_header.h"

static sem_t    *init_forks(t_all *all);
static t_philo  *init_philos(t_all *all);
static sem_t    *init_limit(t_all *all);

int init_forks_and_philos(t_all *all)
{
    all->forks = init_forks(all);
    if (!all->forks)
        return (-1);
    all->ph_limit_sem = init_limit(all);
    if (!all->ph_limit_sem)
        return (-1);
    all->philo = init_philos(all);
    if (!all->philo)
        return (-1);
    return (0);
}

static sem_t    *init_forks(t_all *all)
{
    sem_t   *ret;

    ret = sem_open(FORKS, O_CREAT, 0644, all->num_philos);
    if (ret == SEM_FAILED)
        return (write_err("Open forks sema failed"), NULL);
    return (ret);
}

static sem_t    *init_limit(t_all *all)
{
    sem_t   *ret;

    if (all->num_philos == 1)
        ret = sem_open(LIMITER, O_CREAT, 0644, 1);
    else
        ret = sem_open(LIMITER, O_CREAT, 0644, all->num_philos - 1);
    if (ret == SEM_FAILED)
        return (write_err("Open limiter sema failed"), NULL);
    return (ret);
}

static t_philo  *init_philos(t_all *all)
{
    t_philo *ret;

    ret = (t_philo *) malloc(sizeof(t_philo));
    if (!ret)
        return (write_err("Malloc error"), NULL);
    ret->last_meal = 0;
    ret->meals_eaten = 0;
    ret->num_meals = all->num_eat;
    ret->num_philos = all->num_philos;
    ret->start = 0;
    ret->state = EAT;
    ret->to_die = transform_into_millisec(all->to_die);
    ret->to_eat = transform_into_millisec(all->to_eat);
    ret->to_sleep = transform_into_millisec(all->to_sleep);
    ret->dead_sem = NULL;
    ret->forks_sem = NULL;
    ret->limit_sem = NULL;
    ret->meals_sem = NULL;
    ret->mess_sem = NULL;
    return (ret);
}
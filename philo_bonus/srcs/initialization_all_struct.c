#include "../includes/philo_bonus_header.h"

static int  init_sema_all(t_all *all);

t_all   *init_all_struct(int argc, char **argv)
{
    t_all   *all;

    all = (t_all *) malloc(sizeof(t_all));
    if (!all)
        return (write_err("Malloc error"), NULL);
    all->forks = NULL;
    all->philo = NULL;
    all->ph_limit_sem = NULL;
    all->num_philos  = ft_atol(argv[1]);
    all->to_die = ft_atol(argv[2]);
    all->to_eat = ft_atol(argv[3]);
    all->to_sleep = ft_atol(argv[4]);
    if (argc == 5)
        all->num_eat = -1;
    else if (argc == 6)
        all->num_eat = ft_atol(argv[5]);
    all->philo_meals = 0;
    all->is_dead = 0;
    all->pid_philo = (pid_t *) malloc(sizeof(pid_t) * all->num_philos);
    if (!all->pid_philo)
        return (write_err("Malloc error"), free(all), NULL);
    if (init_sema_all(all) == -1)
        return (free(all->pid_philo), free(all), NULL);
    return (all);
}

static int  init_sema_all(t_all *all)
{
    all->mess_sem = sem_open(MESS, O_CREAT, 0644, 1);
    if (all->mess_sem == SEM_FAILED)
        return (write_err("Open message sema failed"), -1);
    all->dead_sem = sem_open(DEATH, O_CREAT, 0644, 0);
    if (all->dead_sem == SEM_FAILED)
        return (write_err("Open death sema failed"),
            sem_close(all->mess_sem), sem_unlink(MESS), -1);
    all->meals_sem = sem_open(MEALS, O_CREAT, 0644, 0);
    if (all->meals_sem == SEM_FAILED)
        return (write_err("Open meals sema failed"),
            sem_close(all->mess_sem), sem_unlink(MESS),
            sem_close(all->dead_sem), sem_unlink(DEATH), -1);
    all->stop_sem = sem_open(END, O_CREAT, 0644, 0);
    if (all->stop_sem == SEM_FAILED)
        return (write_err("Open stop sema failed"),
            sem_close(all->mess_sem), sem_unlink(MESS),
            sem_close(all->dead_sem), sem_unlink(DEATH),
            sem_close(all->meals_sem), sem_unlink(MEALS), -1);
    return (0);
}

#include "../../includes/philo_bonus_header.h"

static int  try_take_fork(t_philo *philo, long ind);

int philo_try_to_eat(t_philo *philo, long ind)
{
    sem_wait(philo->limit_sem);
    if (check_if_dead(philo, ind, 0) == -1)
        return (sem_post(philo->limit_sem), -1);
    if (try_take_fork(philo, ind) == -1)
        return (-1);
    if (philo->num_philos == 1)
    {
        usleep(philo->to_die * 1000);
        if (check_if_dead(philo, ind, 0) == -1)
            return (sem_post(philo->forks_sem), -1);
    }
    if (try_take_fork(philo, ind) == -1)
        return (sem_post(philo->forks_sem), -1);
    return (0);
}

static int  try_take_fork(t_philo *philo, long ind)
{
    sem_wait(philo->forks_sem);
    if (check_if_dead(philo, ind, 1) == -1)
        return (sem_post(philo->forks_sem), -1);
    sem_wait(philo->mess_sem);
    if (check_if_dead(philo, ind, 1) == -1)
        return (sem_post(philo->forks_sem), -1);
    printf("%lu %li has taken a fork\n", get_curr_time(), ind);
    sem_post(philo->mess_sem);
    return (0);
}

void    philo_eat(t_philo *philo, long ind)
{
    sem_wait(philo->mess_sem);
    if (check_if_dead(philo, ind, 1) == -1)
    {
        sem_post(philo->forks_sem);
        sem_post(philo->forks_sem);
        return ;
    }
    philo->last_meal = get_curr_time();
    printf("%lu %li is eating\n", get_curr_time(), ind);
    sem_post(philo->mess_sem);
    usleep(philo->to_eat * 1000);
    philo->state = SLEEP;
    philo->meals_eaten++;
    sem_post(philo->forks_sem);
    sem_post(philo->forks_sem);
    sem_post(philo->limit_sem);
    return ;
}
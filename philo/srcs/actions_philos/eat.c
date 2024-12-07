#include "../../includes/philo_header.h"

int philo_try_to_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork_mut);
    if (check_if_dead(philo, 0) == 1)
        return (pthread_mutex_unlock(philo->r_fork_mut), -1);
    pthread_mutex_lock(philo->mess_mut);
    if (check_if_dead(philo, 1) == 1)
        return (-1);
    printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
    pthread_mutex_unlock(philo->mess_mut);
    if (philo->num_philos == 1)
        return (0);
    pthread_mutex_lock(philo->l_fork_mut);
    if (check_if_dead(philo, 0) == 1)
        return (pthread_mutex_unlock(philo->l_fork_mut),
            pthread_mutex_unlock(philo->r_fork_mut), -1);
    pthread_mutex_lock(philo->mess_mut);
    if (check_if_dead(philo, 1) == 1)
        return (-1);
    printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
    pthread_mutex_unlock(philo->mess_mut);
    return (0);
}

void    philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->mess_mut);
    if (check_if_dead(philo, 1) == 1)
        return ;
    philo->last_meal = get_curr_time();
    printf("%lu %li is eating\n", philo->last_meal, philo->ind_philo);
    pthread_mutex_unlock(philo->mess_mut);
    usleep(philo->to_eat);
    philo->state = SLEEP;
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->l_fork_mut);
    pthread_mutex_unlock(philo->r_fork_mut);
    return ;
}
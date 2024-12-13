#include "../../includes/philo_bonus_header.h"

int philo_try_to_eat(t_philo *philo, long ind)
{
    sem_wait(FORKS);
    //check_death
    sem_wait(MESS);
    //check_death
    printf("%lu %li has taken a fork\n", get_curr_time(), ind);
    sem_post(MESS);
    if (philo->num_philos == 1)
    {
        usleep(philo->to_die * 1000);
        //check_death
        return (sem_post(FORKS), -1);
    }
    sem_wait(FORKS);
    //check_death
    sem_wait(MESS);
    //check_death
    printf("%lu %li has taken a fork\n", get_curr_time(), ind);
    sem_post(MESS);
    return (0);
}

void    philo_eat(t_philo *philo, long ind)
{
    sem_wait(MESS);
    //check_death
    philo->last_meal = get_curr_time();
    printf("%lu %li is eating\n", get_curr_time(), ind);
    sem_post(MESS);
    usleep(philo->to_eat * 1000);
    philo->state = SLEEP;
    philo->meals_eaten++;
    sem_post(FORKS);
    sem_post(FORKS);
}
#include "../../includes/philo_bonus_header.h"

void    philo_sleep(t_philo *philo, long ind)
{
    sem_wait(MESS);
    //check_death
    printf("%lu %li is sleeping\n", get_curr_time(), ind);
    sem_post(MESS);
    philo->state = THINK;
    usleep(philo->to_sleep * 1000);
    return ;
}
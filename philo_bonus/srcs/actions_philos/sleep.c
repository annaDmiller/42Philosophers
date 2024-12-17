#include "../../includes/philo_bonus_header.h"

void    philo_sleep(t_philo *philo, long ind)
{
    sem_wait(philo->mess_sem);
    if (philo->state == DEAD)
        return ;
    printf("%lu %li is sleeping\n", get_curr_time(), ind);
    sem_post(philo->mess_sem);
    philo->state = THINK;
    usleep(philo->to_sleep * 1000);
    return ;
}
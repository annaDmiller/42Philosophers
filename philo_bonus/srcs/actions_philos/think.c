#include "../../includes/philo_bonus_header.h"

void    philo_think(t_philo *philo, long ind)
{
    sem_wait(philo->mess_sem);
    if (philo->state == DEAD)
        return ;
    printf("%lu %li is thinking\n", get_curr_time(), ind);
    sem_post(philo->mess_sem);
    philo->state = EAT;
    usleep(100);
    return ;
}
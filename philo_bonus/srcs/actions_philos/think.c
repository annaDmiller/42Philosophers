#include "../../includes/philo_bonus_header.h"

void    philo_think(t_philo *philo, long ind)
{
    sem_wait(philo->mess_sem);
    if (check_if_dead(philo, ind, 0) == -1)
        return ;
    printf("%lu %li is thinking\n", get_curr_time(), ind);
    sem_post(philo->mess_sem);
    philo->state = EAT;
    usleep(1000);
    return ;
}
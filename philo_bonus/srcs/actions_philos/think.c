#include "../../includes/philo_bonus_header.h"

void    philo_think(t_philo *philo, long ind)
{
    sem_wait(MESS);
    //check_death
    printf("%lu %li is thinking\n", get_curr_time(), ind);
    sem_post(MESS);
    philo->state = EAT;
    usleep(1000);
    return ;
}
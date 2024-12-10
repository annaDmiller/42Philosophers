#include "../../includes/philo_header.h"

void    philo_think(t_philo *philo)
{
    pthread_mutex_lock(philo->mess_mut);
    if (check_if_dead(philo, 1) == 1)
        return ;
    printf("%lu %li is thinking\n", get_curr_time(), philo->ind_philo);
    pthread_mutex_unlock(philo->mess_mut);
    philo->state = EAT;
    usleep(philo->to_sleep * 1000);
    return ;

}

#include "../../includes/philo_bonus_header.h"

int	check_if_dead(t_philo *philo, long ind, int is_locked)
{
    if (philo->state == DEAD)
        return (-1);
	if (get_curr_time() - philo->last_meal < philo->to_die)
        return (0);
    if (is_locked == 0)
        sem_wait(philo->mess_sem);
    philo->state = DEAD;
    sem_wait(philo->block_sem);
    printf("%lu %li died\n", get_curr_time(), ind);
    sem_post(philo->dead_sem);
    return (-1);
}
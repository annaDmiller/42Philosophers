#include "../../includes/philo_header.h"

int	check_if_dead(t_philo *philo, int is_locked)
{
	if (get_curr_time() - philo->last_meal < philo->to_die)
		return (0);
	if (is_locked == 0)
		pthread_mutex_lock(philo->mess_mut);
	pthread_mutex_lock(&(philo->dead->mut));
	if (philo->dead->is_dead == 1)
		return (pthread_mutex_unlock(philo->mess_mut),
			pthread_mutex_unlock(&(philo->dead->mut)), 1);
	printf("%lu %li died\n", get_curr_time(), philo->ind_philo);
	philo->dead->is_dead = 1;
	pthread_mutex_unlock(&(philo->dead->mut));
	if (is_locked == 0)
		pthread_mutex_unlock(philo->mess_mut);
	philo->state = DEAD;
	return (1);
}

int	check_if_any_dead(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&(philo->dead->mut));
	if (philo->dead->is_dead == 1)
		check = 0;
	pthread_mutex_unlock(&(philo->dead->mut));
	return (check);
}

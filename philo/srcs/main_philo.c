#include "../includes/philo_header.h"

static void	*philo(void *arg);
static int	check_lim_meals(t_philo *philo);

int	main_philo(t_all *all)
{
	long	ind;
	size_t	start;

	ind = -1;
	start = get_curr_time();
	while (++ind < all->num_philos)
	{
		(all->philos[ind]).start = start;
		(all->philos[ind]).last_meal = start;
		if (pthread_create(&((all->philos[ind]).thread),
				NULL, philo, (void *) &(all->philos[ind])) != 0)
			return (write_err("Thread creation failed"),
				detach_thread(all, 0, ind), -1);
	}
	ind = -1;
	while (++ind < all->num_philos)
	{
		if (pthread_join((all->philos[ind]).thread, NULL) != 0)
			return (write_err("Error in thread joining"),
				detach_thread(all, ind, all->num_philos), -1);
	}
	return (0);
}

static void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->lim_meals == 0)
		return (NULL);
	while (philo->state != DEAD && *(philo->dead) == 0)
	{
		if (philo->lim_meals != -1)
			if (check_lim_meals(philo) == 1)
				break ;
		if (check_if_dead(philo, 0) == 1)
			continue ;
		if (philo->state == EAT)
		{
			if (philo_try_to_eat(philo) != -1)
				philo_eat(philo);
		}
		else if (philo->state == SLEEP)
			philo_sleep(philo);
		else if (philo->state == THINK)
			philo_think(philo);
	}
	return (NULL);
}

static int	check_lim_meals(t_philo *philo)
{
	int	check;

	check = 0;
	if (philo->meals_eaten < philo->lim_meals)
		return (0);
	pthread_mutex_lock(philo->lim_eat_mut);
	if (check_if_dead(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->lim_eat_mut), 1);
	if (philo->meals_eaten == philo->lim_meals && philo->state == SLEEP)
		(*(philo->lim_eat_done))++;
	if (*(philo->lim_eat_done) == philo->num_philos)
		check = 1;
	pthread_mutex_unlock(philo->lim_eat_mut);
	return (check);
}

int	check_if_dead(t_philo *philo, int is_locked)
{
	if (get_curr_time() - philo->last_meal < philo->to_die)
		return (0);
	if (is_locked == 0)
		pthread_mutex_lock(philo->mess_mut);
	if (*(philo->dead) == 1)
		return (pthread_mutex_unlock(philo->mess_mut), 1);
	printf("%lu %li died\n", get_curr_time(), philo->ind_philo);
	*(philo->dead) = 1;
	pthread_mutex_unlock(philo->mess_mut);
	philo->state = DEAD;
	return (1);
}

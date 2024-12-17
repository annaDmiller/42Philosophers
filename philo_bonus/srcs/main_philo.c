#include "../includes/philo_bonus_header.h"

static int	open_sems(t_philo *philo);
static void	check_eat_enough(t_philo *philo, long ind);

int	run_philo(t_philo *philo, long ind)
{
	pthread_t	check_death;

	if (open_sems(philo) == -1)
		return (-1);
	philo->ind = ind;
	pthread_create(&check_death, NULL, monitor_death, (void *) philo);
	pthread_detach(check_death);
	while (1)
	{
		if (philo->num_meals != -1)
			check_eat_enough(philo, ind);
		if (philo->state == EAT)
		{
			if (philo_try_to_eat(philo, ind) != -1)
				philo_eat(philo, ind);
		}
		else if (philo->state == SLEEP)
			philo_sleep(philo, ind);
		else if (philo->state == THINK)
			philo_think(philo, ind);
	}
	return (0);
}

static int	open_sems(t_philo *philo)
{
	philo->forks_sem = sem_open(FORKS, 0);
	philo->mess_sem = sem_open(MESS, 0);
	philo->meals_sem = sem_open(MEALS, 0);
	philo->limit_sem = sem_open(LIMITER, 0);
	philo->stop_sem = sem_open(END, 0);
	return (0);
}

static void	check_eat_enough(t_philo *philo, long ind)
{
	if (philo->state != SLEEP)
		return ;
	if (philo->meals_eaten == philo->num_meals)
		sem_post(philo->meals_sem);
	return ;
}

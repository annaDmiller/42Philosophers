#include "../includes/philo_bonus_header.h"

static int	open_sems(t_philo *philo);
static void	check_eat_enough(t_philo *philo, long ind);

int	run_philo(t_philo *philo, long ind)
{
	if (open_sems(philo) == -1)
		return (-1);
	philo->ind = ind;
	while (1)
	{
		if (check_if_dead(philo, ind, 0) == -1)
			continue ;
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
	philo->dead_sem = sem_open(DEATH, 0);
	if (philo->dead_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), -1);
	philo->forks_sem = sem_open(FORKS, 0);
	if (philo->forks_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(philo->dead_sem), -1);
	philo->mess_sem = sem_open(MESS, 0);
	if (philo->mess_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(philo->dead_sem), 
			sem_close(philo->forks_sem), -1);
	philo->meals_sem = sem_open(MEALS, 0);
	if (philo->meals_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(philo->dead_sem), 
			sem_close(philo->forks_sem), 
			sem_close(philo->mess_sem), -1);
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

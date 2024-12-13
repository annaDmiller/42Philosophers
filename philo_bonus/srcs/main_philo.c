#include "../includes/philo_bonus_header.h"

int	philo(t_philo *philo, long ind)
{
    if (philo->num_meals == 0)
        return (0);
	if (open_sems(philo) == -1)
		return (-1);
    while (1)
    {
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
}

static int	open_sems(t_philo *philo)
{
	philo->dead_sem = sem_open(DEATH, 0);
	if (philo->dead_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), -1);
	philo->forks_sem = sem_open(FORKS, 0);
	if (philo->forks_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(DEATH), -1);
	philo->mess_sem = sem_open(MESS, 0);
	if (philo->mess_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(DEATH), sem_close(FORKS), -1);
	philo->meals_sem = sem_open(MEALS, 0);
	if (philo->meals_sem == SEM_FAILED)
		return (write_err("Impossible to open sema"), 
			sem_close(DEATH), sem_close(FORKS), sem_close(MESS),
			-1);
	return (0);
}
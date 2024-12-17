#include "../../includes/philo_bonus_header.h"

static void	clean_philo(t_philo *philo);

void	free_all(t_all *all, int unlink_sem)
{
	if (all->philo)
		clean_philo(all->philo);
	if (all->forks)
		sem_close(all->forks);
	if (all->mess_sem)
		sem_close(all->mess_sem);
	if (all->meals_sem)
		sem_close(all->meals_sem);
	if (all->stop_sem)
		sem_close(all->stop_sem);
	if (all->ph_limit_sem)
		sem_close(all->ph_limit_sem);
	if (unlink_sem)
		unlink_sems();
	if (all->pid_philo)
		free(all->pid_philo);
	free(all);
	return ;
}

static void	clean_philo(t_philo *philo)
{
	if (philo->mess_sem)
		sem_close(philo->mess_sem);
	if (philo->meals_sem)
		sem_close(philo->meals_sem);
	if (philo->forks_sem)
		sem_close(philo->forks_sem);
	if (philo->limit_sem)
		sem_close(philo->limit_sem);
	if (philo->stop_sem)
		sem_close(philo->stop_sem);
	free(philo);
	return ;
}

void	unlink_sems(void)
{
	sem_unlink(MESS);
	sem_unlink(MEALS);
	sem_unlink(END);
	sem_unlink(FORKS);
	sem_unlink(DEATH);
	sem_unlink(LIMITER);
	return ;
}

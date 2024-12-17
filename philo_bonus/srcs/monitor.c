#include "../includes/philo_bonus_header.h"

void	monitor_meals(t_all *all)
{
	sem_t	*meals;
	sem_t	*end;
	long	ind;
	sem_t	*mess;

	meals = sem_open(MEALS, 0);
	end = sem_open(END, 0);
	mess = sem_open(MESS, 0);
	ind = -1;
	while (++ind < all->num_philos)
		sem_wait(meals);
	sem_wait(mess);
	printf("Philosophers ate enough time\n");
	sem_post(end);
	sem_close(meals);
	sem_close(end);
	free_all(all, 0);
	exit(0);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->last_meal + philo->to_die > get_curr_time())
			continue ;
		philo->state = DEAD;
		sem_wait(philo->mess_sem);
		printf("%lu %li died\n", get_curr_time(), philo->ind);
		printf("One or more philosophers died\n");
		sem_post(philo->stop_sem);
		break ;
	}
	return (NULL);
}

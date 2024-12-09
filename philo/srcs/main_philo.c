/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:05 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:06 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (1)
	{
		if (check_if_any_dead(philo) == 1)
			break ;
		if (philo->lim_meals != -1)
			if (check_lim_meals(philo) == 1)
				break ;
		if (philo->state == EAT)
		{
			if (philo_try_to_eat(philo) != -1)
				philo_eat(philo);
		}
		else if (philo->state == SLEEP)
			philo_sleep(philo);
		else if (philo->state == THINK)
			philo_think(philo);
		if (check_if_to_die(philo, 0) == 1)
			break ;
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
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->lim_eat_mut), 1);
	if (philo->meals_eaten == philo->lim_meals && philo->state == SLEEP)
		(*(philo->lim_eat_done))++;
	if (*(philo->lim_eat_done) == philo->num_philos)
		check = 1;
	pthread_mutex_unlock(philo->lim_eat_mut);
	return (check);
}

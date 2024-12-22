/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:11:49 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/20 13:11:52 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_header.h"

static int	death_checker(t_philo *philo);

void	*monitor_end(void *arg)
{
	t_all	*all;
	long	ind;

	all = (t_all *) arg;
	while (1)
	{
		ind = -1;
		while (++ind < all->num_philos)
			if (death_checker(&(all->philos[ind])) == 1)
				return (NULL);
	}
	return (NULL);
}

static int	death_checker(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->time_mut));
		if (get_curr_time() - philo->last_meal < philo->to_die)
		{
			pthread_mutex_unlock(&(philo->time_mut));
			continue ;
		}
		pthread_mutex_unlock(&(philo->time_mut));
		if (philo->lim_meals != -1 && check_lim_meals(philo, 0) == 1)
			return (1);
		pthread_mutex_lock(philo->dead_mut);
		if (*philo->dead == 1)
			return (pthread_mutex_unlock(philo->dead_mut), 1);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_mut);
		pthread_mutex_lock(philo->mess_mut);
		printf("%lu %li died\n", get_curr_time(), philo->ind_philo);
		pthread_mutex_unlock(philo->mess_mut);
	}
	return (1);
}

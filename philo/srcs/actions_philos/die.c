/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:05:51 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 10:06:31 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

int	check_if_any_dead(t_philo *philo, int mess_locked)
{
	int	check;

	check = 0;
	pthread_mutex_lock(philo->dead_mut);
	if (*philo->dead == 1)
		check = 1;
	pthread_mutex_unlock(philo->dead_mut);
	if (mess_locked == 1 && check == 1)
		pthread_mutex_unlock(philo->mess_mut);
	return (check);
}

int	death_checker(t_philo *philo)
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
		philo->state = DEAD;
	}
	return (1);
}

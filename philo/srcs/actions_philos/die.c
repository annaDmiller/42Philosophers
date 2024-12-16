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

int	check_if_to_die(t_philo *philo, int is_locked)
{
	if (check_if_any_dead(philo, 1) == 1)
		return (1);
	if (get_curr_time() - philo->last_meal < philo->to_die)
		return (0);
	pthread_mutex_lock(philo->dead_mut);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_mut),
			pthread_mutex_unlock(philo->mess_mut), 1);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_mut);
	if (is_locked == 0)
		pthread_mutex_lock(philo->mess_mut);
	printf("%lu %li died\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	philo->state = DEAD;
	return (1);
}

void	*death_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (get_curr_time() - philo->last_meal < philo->to_die)
			continue ;
		pthread_mutex_lock(philo->dead_mut);
		if (*philo->dead == 1)
			return (pthread_mutex_unlock(philo->dead_mut), NULL);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_mut);
		pthread_mutex_lock(philo->mess_mut);
		printf("%lu %li died\n", get_curr_time(), philo->ind_philo);
		pthread_mutex_unlock(philo->mess_mut);
		philo->state = DEAD;
		break ;
	}
	return (NULL);
}

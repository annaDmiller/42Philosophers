/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:23 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:25 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

static void	take_right_fork(t_philo *philo);
static void	take_left_fork(t_philo *philo);

int	philo_try_to_eat(t_philo *philo)
{
	take_right_fork(philo);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_any_dead(philo, 1) == 1)
		return (pthread_mutex_unlock(&(philo->r_fork_mut->fork_mut)), -1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	if (philo->num_philos == 1)
		return (usleep(philo->to_die * 1000), check_if_any_dead(philo, 0),
			pthread_mutex_unlock(&(philo->r_fork_mut->fork_mut)), -1);
	take_left_fork(philo);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_any_dead(philo, 1) == 1)
		return (pthread_mutex_unlock(&(philo->l_fork_mut->fork_mut)),
			pthread_mutex_unlock(&(philo->r_fork_mut->fork_mut)), -1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	return (0);
}

static void	take_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->r_fork_mut->fork_mut));
		if (philo->ind_philo == philo->r_fork_mut->queue)
			break ;
		pthread_mutex_unlock(&(philo->r_fork_mut->fork_mut));
	}
	if (philo->ind_philo == 1)
		philo->r_fork_mut->queue = philo->num_philos;
	else
		philo->r_fork_mut->queue = philo->ind_philo - 1;
	return ;
}

static void	take_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->l_fork_mut->fork_mut));
		if (philo->ind_philo == philo->l_fork_mut->queue)
			break ;
		pthread_mutex_unlock(&(philo->l_fork_mut->fork_mut));
	}
	if (philo->ind_philo == philo->num_philos)
		philo->l_fork_mut->queue = 1;
	else
		philo->l_fork_mut->queue = philo->ind_philo + 1;
	return ;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mess_mut);
	pthread_mutex_lock(&(philo->time_mut));
	if (check_if_any_dead(philo, 1) == 1)
	{
		pthread_mutex_unlock(&(philo->time_mut));
		return ;
	}
	philo->last_meal = get_curr_time();
	printf("%lu %li is eating\n", philo->last_meal, philo->ind_philo);
	pthread_mutex_unlock(&(philo->time_mut));
	pthread_mutex_unlock(philo->mess_mut);
	usleep(philo->to_eat * 1000);
	philo->state = SLEEP;
	philo->meals_eaten++;
	pthread_mutex_unlock(&(philo->r_fork_mut->fork_mut));
	pthread_mutex_unlock(&(philo->l_fork_mut->fork_mut));
	return ;
}

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

static int	philo_even_try_eat(t_philo *philo);
static int	philo_odd_try_eat(t_philo *philo);

int	philo_try_to_eat(t_philo *philo)
{
	if (philo->ind_philo % 2 == 1)
		return (philo_odd_try_eat(philo));
	return (philo_even_try_eat(philo));
}

static int	philo_odd_try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork_mut);
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->r_fork_mut), -1);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_to_die(philo, 1) == 1)
		return (-1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	if (philo->num_philos == 1)
	{
		usleep(philo->to_die * 1000);
		check_if_to_die(philo, 0);
		return (pthread_mutex_unlock(philo->r_fork_mut), -1);
	}
	pthread_mutex_lock(philo->l_fork_mut);
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->l_fork_mut),
			pthread_mutex_unlock(philo->r_fork_mut), -1);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_to_die(philo, 1) == 1)
		return (-1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	return (0);
}

static int	philo_even_try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork_mut);
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->l_fork_mut), -1);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_to_die(philo, 1) == 1)
		return (-1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	pthread_mutex_lock(philo->r_fork_mut);
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->r_fork_mut),
			pthread_mutex_unlock(philo->l_fork_mut), -1);
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_to_die(philo, 1) == 1)
		return (-1);
	printf("%lu %li has taken a fork\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_to_die(philo, 1) == 1)
		return ;
	philo->last_meal = get_curr_time();
	printf("%lu %li is eating\n", philo->last_meal, philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	usleep(philo->to_eat * 1000);
	philo->state = SLEEP;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->r_fork_mut);
	pthread_mutex_unlock(philo->l_fork_mut);
	return ;
}

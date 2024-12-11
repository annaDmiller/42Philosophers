/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:30 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:31 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_dead(philo, 1) == 1)
		return ;
	printf("%lu %li is sleeping\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	philo->state = THINK;
	usleep(philo->to_sleep * 1000);
	return ;
}

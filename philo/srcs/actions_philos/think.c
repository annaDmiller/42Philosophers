/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:27 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:28 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->mess_mut);
	if (check_if_any_dead(philo, 1) == 1)
		return ;
	printf("%lu %li is thinking\n", get_curr_time(), philo->ind_philo);
	pthread_mutex_unlock(philo->mess_mut);
	usleep(100);
	philo->state = EAT;
	return ;
}

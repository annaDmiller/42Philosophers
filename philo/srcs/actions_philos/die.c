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

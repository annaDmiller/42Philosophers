/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:43 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:44 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

void	free_all(t_all *all, int destroy_forks)
{
	long	ind;

	if (all->forks)
	{
		if (destroy_forks)
			mut_destroy(all->forks, all->num_philos);
		free(all->forks);
	}
	if (all->philos)
		free(all->philos);
	pthread_mutex_destroy(&((all->fin).mut));
	pthread_mutex_destroy(&(all->mess));
	free(all);
	return ;
}

void	mut_destroy(pthread_mutex_t *forks, long stop_at)
{
	long	ind;

	ind = 0;
	while (ind < stop_at)
	{
		pthread_mutex_destroy(&(forks[ind]));
		ind++;
	}
	return ;
}

void	detach_thread(t_all *all, long start_at, long stop_at)
{
	long	ind;

	ind = start_at;
	while (ind < stop_at)
	{
		if ((all->philos[ind]).thread != 0)
			pthread_detach((all->philos[ind]).thread);
		ind++;
	}
	return ;
}

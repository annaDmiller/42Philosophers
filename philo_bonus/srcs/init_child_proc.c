/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_child_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:12:27 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/20 13:12:28 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus_header.h"

int	run_child_proc(t_all *all)
{
	long	ind;

	ind = -1;
	while (++ind < all->num_philos)
	{
		all->pid_philo[ind] = fork();
		if (all->pid_philo[ind] < 0)
			return (fork_failed(all, ind), -1);
		else if (all->pid_philo[ind] == 0)
		{
			if (run_philo(all->philo, ind + 1) == -1)
			{
				free_all(all, 1);
				exit (1);
			}
			free_all(all, 0);
			exit(0);
		}
	}
	return (0);
}

void	fork_failed(t_all *all, long stop_at)
{
	long	ind;

	ind = -1;
	sem_wait(all->mess_sem);
	write_err("Impossible to create a child process");
	while (++ind < stop_at)
		kill(all->pid_philo[ind], SIGKILL);
	printf("Simulation is stopped\n");
	sem_post(all->mess_sem);
	return ;
}

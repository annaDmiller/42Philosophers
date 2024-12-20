/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:12:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/20 13:12:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus_header.h"

static int	run_program(t_all *all);
static int	wait_end(t_all *all, pid_t check_stop);

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (write_err("You need to input 4 or 5 arguements"), 1);
	all = NULL;
	if (!validate_args(argc, argv))
		return (1);
	unlink_sems();
	all = init_all_struct(argc, argv);
	if (!all)
		return (1);
	if (check_intro_values(all, argc) == -1)
		return (free_all(all, 0), 1);
	if (init_forks_and_philos(all) == -1)
		return (free_all(all, 0), 1);
	if (run_program(all) == -1)
		return (free_all(all, 1), 1);
	free_all(all, 1);
	return (0);
}

static int	run_program(t_all *all)
{
	pid_t	pid_monitor;

	printf("Launch of program at %lu\n", get_curr_time());
	all->philo->start = get_curr_time();
	all->philo->last_meal = all->philo->start;
	if (run_child_proc(all) == -1)
		return (-1);
	if (all->num_eat != -1)
	{
		pid_monitor = fork();
		if (pid_monitor < 0)
		{
			fork_failed(all, all->num_philos);
			return (-1);
		}
		else if (pid_monitor == 0)
			monitor_meals(all);
	}
	wait_end(all, pid_monitor);
	return (0);
}

static int	wait_end(t_all *all, pid_t pid_monitor)
{
	long	ind;

	ind = -1;
	sem_wait(all->stop_sem);
	if (all->num_eat != -1)
		kill(pid_monitor, SIGKILL);
	while (++ind < all->num_philos)
		kill(all->pid_philo[ind], SIGKILL);
	printf("Simulation is stopped\n");
	return (0);
}

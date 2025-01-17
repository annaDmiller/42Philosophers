/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:00 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:01 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_header.h"

static int	run_program(t_all *all);

int	main(int argc, char **argv)
{
	struct s_all	*all;

	if (argc < 5 || argc > 6)
		return (write_err("You need to input 4 or 5 arguements"), 1);
	all = NULL;
	if (!validate_args(argc, argv))
		return (1);
	all = init_all(argc, argv);
	if (!all)
		return (1);
	if (check_intro_values(all, argc) == -1)
		return (free_all(all, 0), 1);
	if (init_forks_and_philos(all) == -1)
		return (free_all(all, 0), 1);
	if (run_program(all) == -1)
		return (free_all(all, 1), 1);
	if (all->is_dead == 1)
		printf("One or more philosophers died\n");
	else if (argc == 6 && ((all->fin).num_philo_eaten == all->num_philos
			|| all->num_eat == 0))
		printf("All philosophers ate enough times\n");
	printf("Simulation is stopped\n");
	free_all(all, 1);
	return (0);
}

static int	run_program(t_all *all)
{
	long		ind;
	size_t		start;
	pthread_t	monitor;

	ind = -1;
	start = get_curr_time();
	printf("Launch of program at %lu\n", start);
	if (all->num_eat == 0)
		return (0);
	while (++ind < all->num_philos)
	{
		(all->philos[ind]).start = start;
		(all->philos[ind]).last_meal = start;
		pthread_create(&((all->philos[ind]).thread),
			NULL, philo, (void *) &(all->philos[ind]));
	}
	pthread_create(&(monitor), NULL, monitor_end, (void *) all);
	ind = -1;
	while (++ind < all->num_philos)
		pthread_join((all->philos[ind]).thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}

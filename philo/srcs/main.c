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
	if (main_philo(all) == -1)
		return (free_all(all, 1), 1);
	if (all->is_dead == 1)
		printf("Reason of finish: One or more philosophers are dead\n");
	else if (argc == 6 && ((all->fin).num_philo_eaten == all->num_philos
			|| (all->fin).num_philo_eaten == 0))
		printf("Reason of finish: All philosophers ate enough times\n");
	free_all(all, 1);
	return (0);
}

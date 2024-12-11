/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_all_struct.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 10:05:39 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_header.h"

static int	init_mutex_all(t_all *all);

t_all	*init_all(int argc, char **argv)
{
	t_all	*all;

	all = (t_all *) malloc(sizeof(t_all));
	if (!all)
		return (write_err("Malloc error"), NULL);
	all->forks = NULL;
	all->philos = NULL;
	if (init_mutex_all(all) == -1)
		return (free(all), NULL);
	(all->fin).num_philo_eaten = 0;
	all->is_dead = 0;
	all->num_philos = ft_atol(argv[1]);
	all->to_die = ft_atol(argv[2]);
	all->to_eat = ft_atol(argv[3]);
	all->to_sleep = ft_atol (argv[4]);
	if (argc == 5)
		all->num_eat = -1;
	else if (argc == 6)
		all->num_eat = ft_atol(argv[5]);
	return (all);
}

static int	init_mutex_all(t_all *all)
{
	if (pthread_mutex_init(&(all->fin.mut), NULL) == -1)
		return (write_err("Impossible to init mutex"), -1);
	if (pthread_mutex_init(&(all->mess), NULL) == -1)
		return (write_err("Impossible to init mutex"),
			pthread_mutex_destroy(&(all->fin.mut)), -1);
	if (pthread_mutex_init(&(all->dead), NULL) == -1)
		return (write_err("Impossible to init mutex"),
			pthread_mutex_destroy(&(all->fin.mut)),
			pthread_mutex_destroy(&(all->mess)), -1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_header.h"

static pthread_mutex_t	*init_forks(t_all *all);
static t_philo			*init_philos(t_all *all);
static void				init_l_r_forks(t_all *all, long ind, t_philo *philo);

int	init_forks_and_philos(t_all *all)
{
	all->forks = init_forks(all);
	if (!all->forks)
		return (write_err("Malloc error"), -1);
	all->philos = init_philos(all);
	if (!all->philos)
		return (write_err("Malloc error"), -1);
	return (0);
}

static pthread_mutex_t	*init_forks(t_all *all)
{
	pthread_mutex_t	*ret;
	long			ind;

	ret = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * all->num_philos);
	if (!ret)
		return (NULL);
	ind = -1;
	while (++ind < all->num_philos)
	{
		if (pthread_mutex_init(&(ret[ind]), NULL) == -1)
			return (write_err("Mutex init error"),
				mut_destroy(ret, ind), free(ret), NULL);
	}
	return (ret);
}

static t_philo	*init_philos(t_all *all)
{
	t_philo	*ret_arr;
	long	ind;

	ret_arr = (t_philo *) malloc(all->num_philos * sizeof(t_philo));
	if (!ret_arr)
		return (NULL);
	ind = -1;
	while (++ind < all->num_philos)
	{
		ret_arr[ind].lim_eat_mut = &(all->fin.mut);
		ret_arr[ind].dead = &(all->is_dead);
		init_l_r_forks(all, ind, ret_arr);
		ret_arr[ind].meals_eaten = 0;
		ret_arr[ind].mess_mut = &(all->mess);
		ret_arr[ind].ind_philo = ind + 1;
		ret_arr[ind].start = 0;
		ret_arr[ind].last_meal = 0;
		ret_arr[ind].state = 0;
		ret_arr[ind].to_die = transform_into_millisec(all->to_die);
		ret_arr[ind].to_eat = transform_into_millisec(all->to_eat);
		ret_arr[ind].to_sleep = transform_into_millisec(all->to_sleep);
		ret_arr[ind].lim_eat_done = &((all->fin).num_philo_eaten);
		ret_arr[ind].lim_meals = all->num_eat;
	}
	return (ret_arr);
}

static void	init_l_r_forks(t_all *all, long ind, t_philo *philo)
{
	if (all->num_philos != 1)
	{
		if (ind == all->num_philos - 1)
			philo[ind].l_fork_mut = &(all->forks[0]);
		else
			philo[ind].l_fork_mut = &(all->forks[ind + 1]);
	}
	philo[ind].r_fork_mut = &(all->forks[ind]);
	philo[ind].num_philos = all->num_philos;
	philo[ind].dead_mut = &(all->dead);
	return ;
}

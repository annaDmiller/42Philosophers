/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:05 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:06 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_header.h"

static int	check_lim_meals(t_philo *philo);

void	*philo(void *arg)
{
	t_philo		*philo;
	pthread_t	check_death;

	philo = (t_philo *) arg;
	if (philo->lim_meals == 0)
		return (NULL);
	pthread_create(&check_death, NULL, death_checker, arg);
	while (1)
	{
		if (check_if_any_dead(philo, 0) == 1)
			break ;
		if (philo->lim_meals != -1)
			if (check_lim_meals(philo) == 1)
				break ;
		if (philo->state == EAT)
		{
			if (philo_try_to_eat(philo) != -1)
				philo_eat(philo);
		}
		else if (philo->state == SLEEP)
			philo_sleep(philo);
		else if (philo->state == THINK)
			philo_think(philo);
	}
	return (pthread_join(check_death, NULL), NULL);
}

static int	check_lim_meals(t_philo *philo)
{
	int	check;

	check = 0;
	if (philo->meals_eaten < philo->lim_meals)
		return (0);
	pthread_mutex_lock(philo->lim_eat_mut);
	if (check_if_to_die(philo, 0) == 1)
		return (pthread_mutex_unlock(philo->lim_eat_mut), 1);
	if (philo->meals_eaten == philo->lim_meals && philo->state == SLEEP)
		(*(philo->lim_eat_done))++;
	if (*(philo->lim_eat_done) == philo->num_philos)
		check = 1;
	pthread_mutex_unlock(philo->lim_eat_mut);
	return (check);
}

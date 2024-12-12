/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:11 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:12 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus_header.h"

int	validate_args(int argc, char **argv)
{
	int	ind_arg;
	int	ind_car;

	ind_arg = 0;
	while (++ind_arg < argc)
	{
		ind_car = -1;
		while (argv[ind_arg][++ind_car])
		{
			if (ind_car == 0 && argv[ind_arg][ind_car] == '-'
				&& ft_isdigit(argv[ind_arg][ind_car + 1]))
				continue ;
			if (!ft_isdigit(argv[ind_arg][ind_car]))
			{
				return (write_err("Incorrect input values. Please, check them"),
					0);
			}
		}
	}
	return (1);
}

int	check_intro_values(t_all *all, int argc)
{
	if (all->num_philos <= 0 || all->to_die <= 0
		|| all->to_eat <= 0 || all->to_sleep <= 0)
		return (write_err("Incorrect input values. Please, check them"),
			-1);
	if (argc == 6 && all->num_eat < 0)
		return (write_err("Incorrect input values. Please, check them"),
			-1);
	return (0);
}

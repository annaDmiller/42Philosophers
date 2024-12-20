/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:50 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/20 13:13:46 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus_header.h"

long	ft_atol(const char *nptr)
{
	long	number;
	long	ind;
	long	sign;

	if (!nptr)
		return (0);
	ind = 0;
	number = 0;
	sign = 1;
	while (nptr[ind] == ' ' || (nptr[ind] >= 9 && nptr[ind] <= 13))
		ind++;
	if (nptr[ind] == '-' || nptr[ind] == '+')
		if (nptr[ind++] == '-')
			sign *= -1;
	while (nptr[ind] >= '0' && nptr[ind] <= '9')
	{
		number = 10 * number + nptr[ind] - 48;
		ind++;
	}
	return (sign * number);
}

size_t	ft_strlen(char *str)
{
	size_t	ind;

	if (!str)
		return (0);
	ind = 0;
	while (str[ind])
		ind++;
	return (ind);
}

int	ft_isdigit(char car)
{
	if (car >= '0' && car <= '9')
		return (1);
	return (0);
}

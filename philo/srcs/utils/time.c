/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:14:54 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:14:55 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_header.h"

size_t	get_curr_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (write_err("gettimeofday() error"), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	transform_into_millisec(long time)
{
	if (time <= UINT_MAX && time >= 0)
		return ((size_t) time);
	if (time < 0)
		return (0);
	return (UINT_MAX);
}

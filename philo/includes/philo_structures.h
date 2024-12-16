/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 08:13:52 by amelniko          #+#    #+#             */
/*   Updated: 2024/12/11 08:13:53 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTURES_H
# define PHILO_STRUCTURES_H

# include <pthread.h>

typedef enum state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_state;

typedef struct s_fin
{
	int				num_philo_eaten;
	pthread_mutex_t	mut;
}					t_fin;

typedef struct s_philo
{
	pthread_t		thread;
	long			num_philos;
	long			ind_philo;
	long			lim_meals;
	t_state			state;
	long			meals_eaten;
	size_t			to_sleep;
	size_t			to_eat;
	size_t			to_die;
	size_t			last_meal;
	size_t			start;
	int				*dead;
	int				*lim_eat_done;
	pthread_mutex_t	*mess_mut;
	pthread_mutex_t	*lim_eat_mut;
	pthread_mutex_t	*r_fork_mut;
	pthread_mutex_t	*l_fork_mut;
	pthread_mutex_t	*dead_mut;
	pthread_mutex_t	time_mut;
}					t_philo;

typedef struct s_all
{
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	long			to_sleep;
	long			to_eat;
	long			num_philos;
	long			to_die;
	long			num_eat;
	int				is_dead;
	pthread_mutex_t	mess;
	pthread_mutex_t	dead;
	t_fin			fin;
}					t_all;

#endif

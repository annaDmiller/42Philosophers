#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include "philo_structures.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

//utils
long	ft_atol(const char *nptr);
size_t	ft_strlen(char *str);
size_t	get_curr_time(void);
size_t	transform_into_millisec(long time);
int		ft_isdigit(char car);

//initialization
t_all	*init_all(int argc, char **argv);
int		init_forks_and_philos(t_all *all);

//finalization and errors writing
void	write_err(char *str);
void	free_all(t_all *all, int destroy_forks);
void	mut_destroy(pthread_mutex_t *forks, long stop_at);
void	detach_thread(t_all *all, long start_at, long stop_at);

//lexer
int		check_intro_values(t_all *all, int argc);
int		validate_args(int argc, char **argv);

int		main_philo(t_all *all);
int		check_if_dead(t_philo *philo, int is_locked);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		philo_try_to_eat(t_philo *philo);
void	philo_eat(t_philo *philo);
#endif

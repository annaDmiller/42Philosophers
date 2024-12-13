#ifndef PHILO_BONUS_HEADER_H
# define PHILO_BONUS_HEADER_H
# include "./philo_bonus_structures.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

int     validate_args(int argc, char **argv);
int	    check_intro_values(t_all *all, int argc);

t_all   *init_all_struct(int argc, char **argv);
int     init_forks_and_philos(t_all *all);

void	write_err(char *str);
void    free_all(t_all *all, int unlink_sem);

long	ft_atol(const char *nptr);
size_t	ft_strlen(char *str);
int	    ft_isdigit(char car);
size_t	get_curr_time(void);
size_t	transform_into_millisec(long time);

void    philo_sleep(t_philo *philo, long ind);
void    philo_think(t_philo *philo, long ind);

#endif
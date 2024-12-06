#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include "philo_structures.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

//utils
long    ft_atol(const char *nptr);
size_t  ft_strlen(char *str);

//initialization
t_all   *init_all(int argc, char **argv);
int     init_forks_and_philos(t_all *all);

//finalization and errors writing
void    write_err(char *str);
void    free_all(t_all *all);
void    mut_destroy_err(t_all *all, int ind);

//lexer
int     check_intro_values(t_all *all, int argc);


#endif
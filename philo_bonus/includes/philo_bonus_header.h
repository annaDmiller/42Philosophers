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

int	validate_args(int argc, char **argv);

#endif
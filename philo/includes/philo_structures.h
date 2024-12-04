#ifndef PHILO_STRUCTURES_H
# define PHILO_STRUCTURES_H

# include <pthread.h>

typedef struct s_state
{
    unsigned int    num_eat;
    char            state;
}           t_state;

#endif
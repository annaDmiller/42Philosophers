#ifndef PHILO_STRUCTURES_H
# define PHILO_STRUCTURES_H

# include <pthread.h>

typedef struct s_philo
{
    char            state;
    unsigned long   eat_times;
    struct timeval  *tv;
    void            *tz;
    long            num_ph;
}                  t_philo;

typedef struct s_all
{
    pthread_mutex_t *forks;
    struct s_philo  *philos;
    long            to_sleep;
    long            to_eat;
    long            num_philos;
    long            to_die;
    long            num_eat;
    int             is_dead;
    pthread_mutex_t mess;
}                   t_all;

#endif
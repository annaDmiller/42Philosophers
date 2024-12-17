#ifndef PHILO_BONUS_STRRUCTURES_H
# define PHILO_BONUS_STRRUCTURES_H
# define MESS "/message_sem"
# define END "/end_sem"
# define DEATH "/death_sem"
# define MEALS "/meals_sem"
# define FORKS "/forks_sem"
# define LIMITER "/limit_sem"

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
# include <signal.h>

typedef enum state
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_state;

typedef struct s_philo
{
	size_t		start;
	size_t		last_meal;
	size_t		to_die;
	size_t		to_sleep;
	size_t		to_eat;
	long		num_philos;
	long		num_meals;
	t_state		state;
	long		meals_eaten;
	long		ind;
	sem_t		*mess_sem;
	sem_t		*dead_sem;
	sem_t		*meals_sem;
	sem_t		*forks_sem;
	sem_t		*limit_sem;
	sem_t		*stop_sem;
}		t_philo;

typedef struct s_all
{
	sem_t			*forks;
	struct s_philo	*philo;
	pid_t			*pid_philo;
	long			to_sleep;
	long			to_eat;
	long			num_philos;
	long			to_die;
	long			num_eat;
	int				is_dead;
	long			philo_meals;
	sem_t	        *mess_sem;
	sem_t	        *dead_sem;
	sem_t			*meals_sem;
	sem_t			*stop_sem;
	sem_t			*ph_limit_sem;
}					t_all;

#endif

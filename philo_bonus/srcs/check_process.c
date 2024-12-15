#include "../includes/philo_bonus_header.h"

static void *check_death(void *arg);
static void *check_meals(void *arg);

void    run_check_stop(t_all *all)
{
    pthread_t   death_check;
    pthread_t   meals_check;

    pthread_create(&death_check, NULL, check_death, (void *) all);
    if (all->num_eat != -1)
    {
        pthread_create(&meals_check, NULL, check_meals, (void *) all);
        pthread_detach(meals_check);
    }
    pthread_join(death_check, NULL);
    free_all(all, 0);
    exit(0);
}

static void *check_death(void *arg)
{
    t_all   *all;
    sem_t   *death;
    sem_t   *end;
    
    all = (t_all *) arg;
    death = sem_open(DEATH, 0);
    end = sem_open(END, 0);
    sem_wait(death);
    printf("One or more philosophers died\n");
    sem_post(end);
    sem_close(death);
    sem_close(end);
    return (NULL);
}

static void *check_meals(void *arg)
{
    t_all   *all;
    sem_t   *meals;
    sem_t   *end;
    long    ind;
    
    all = (t_all *) arg;
    meals = sem_open(MEALS, 0);
    end = sem_open(END, 0);
    ind = -1;
    while (++ind < all->num_philos)
        sem_wait(meals);
    if (ind == all->num_philos)
    {
        printf("Philosophers ate enough time\n");
        sem_post(end);
    }
    sem_close(meals);
    sem_close(end);
    return (NULL);
}


#include "../includes/philo_header.h"

static pthread_mutex_t	*init_forks(t_all *all);
static t_philo			*init_philos(t_all *all);
static void				init_l_r_forks(t_all *all, long ind, t_philo *philo);

t_all	*init_all(int argc, char **argv)
{
	t_all	*all;

	all = (t_all *) malloc(sizeof(t_all));
	if (!all)
		return (write_err("Malloc error"), NULL);
	all->forks = NULL;
	all->philos = NULL;
	(all->fin).num_philo_eaten = 0;
	if (pthread_mutex_init(&(all->fin.mut), NULL) == -1)
		return (write_err("Impossible to init mutex"), free(all), NULL);
	if (pthread_mutex_init(&(all->mess), NULL) == -1)
		return (write_err("Impossible to init mutex"),
			pthread_mutex_destroy(&(all->fin.mut)), free(all), NULL);
	all->is_dead = 0;
	all->num_philos = ft_atol(argv[1]);
	all->to_die = ft_atol(argv[2]);
	all->to_eat = ft_atol(argv[3]);
	all->to_sleep = ft_atol (argv[4]);
	if (argc == 5)
		all->num_eat = -1;
	else if (argc == 6)
		all->num_eat = ft_atol(argv[5]);
	return (all);
}

int	init_forks_and_philos(t_all *all)
{
	all->forks = init_forks(all);
	if (!all->forks)
		return (write_err("Malloc error"), -1);
	all->philos = init_philos(all);
	if (!all->philos)
		return (write_err("Malloc error"), -1);
	return (0);
}

static pthread_mutex_t	*init_forks(t_all *all)
{
	pthread_mutex_t	*ret;
	long			ind;

	ret = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * all->num_philos);
	if (!ret)
		return (NULL);
	ind = -1;
	while (++ind < all->num_philos)
	{
		if (pthread_mutex_init(&(ret[ind]), NULL) == -1)
			return (write_err("Mutex init error"),
				mut_destroy(ret, ind), free(ret), NULL);
	}
	return (ret);
}

static t_philo	*init_philos(t_all *all)
{
	t_philo	*ret_arr;
	long	ind;

	ret_arr = (t_philo *) malloc(all->num_philos * sizeof(t_philo));
	if (!ret_arr)
		return (NULL);
	ind = -1;
	while (++ind < all->num_philos)
	{
		ret_arr[ind].lim_eat_mut = &(all->fin.mut);
		ret_arr[ind].dead = &(all->is_dead);
		init_l_r_forks(all, ind, ret_arr);
		ret_arr[ind].meals_eaten = 0;
		ret_arr[ind].mess_mut = &(all->mess);
		ret_arr[ind].ind_philo = ind + 1;
		ret_arr[ind].start = 0;
		ret_arr[ind].last_meal = 0;
		ret_arr[ind].state = 0;
		ret_arr[ind].to_die = transform_into_millisec(all->to_die);
		ret_arr[ind].to_eat = transform_into_millisec(all->to_eat);
		ret_arr[ind].to_sleep = transform_into_millisec(all->to_sleep);
		ret_arr[ind].lim_eat_done = &((all->fin).num_philo_eaten);
		ret_arr[ind].lim_meals = all->num_eat;
	}
	return (ret_arr);
}

static void	init_l_r_forks(t_all *all, long ind, t_philo *philo)
{
	if (all->num_philos != 1)
	{
		if (ind == all->num_philos - 1)
			philo[ind].l_fork_mut = &(all->forks[0]);
		else
			philo[ind].l_fork_mut = &(all->forks[ind + 1]);
	}
	philo[ind].r_fork_mut = &(all->forks[ind]);
	philo[ind].num_philos = all->num_philos;
	return ;
}

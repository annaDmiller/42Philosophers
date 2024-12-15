#include "../includes/philo_bonus_header.h"

static int	run_program(t_all *all);
static int	wait_end(t_all *all, pid_t check_stop);
static void	fork_failed(t_all *all, long ind);

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (write_err("You need to input 4 or 5 arguements"), 1);
	all = NULL;
	if (!validate_args(argc, argv))
		return (1);
	unlink_sems();
	all = init_all_struct(argc, argv);
	if (!all)
		return (1);
	if (check_intro_values(all, argc) == -1)
		return (free_all(all, 0), 1);
	if (init_forks_and_philos(all) == -1)
		return (free_all(all, 0), 1);
	if (run_program(all) == -1)
		return (free_all(all, 1), 1);
	free_all(all, 1);
	return (0);
}

static int	run_program(t_all *all)
{
	long	ind;
	pid_t	check_stop;
	int		check;

	ind = -1;
	all->philo->start = get_curr_time();
	all->philo->last_meal = all->philo->start;
	check = 0;
	while (++ind < all->num_philos)
	{
		all->pid_philo[ind] = fork();
		if (all->pid_philo[ind] < 0)
			return (fork_failed(all, ind), -1);
		else if (all->pid_philo[ind] == 0)
		{
			if (run_philo(all->philo, ind + 1) == -1)
			{
				free_all(all, 1);
				exit (1);
			}
			return (0);
		}
	}
	check_stop = fork();
	if (check_stop < 0)
		fork_failed(all, all->num_philos);
	else if (check_stop == 0)
		run_check_stop(all);
	else if (check_stop > 0)
		wait_end(all, check_stop);
	return (0);
}

static int	wait_end(t_all *all, pid_t check_stop)
{
	long	ind;

	ind = -1;
	sem_wait(all->stop_sem);
	while (++ind < all->num_philos)
		kill(all->pid_philo[ind], SIGKILL);
	kill(check_stop, SIGKILL);
	printf("Simulation is stopped\n");
	return (0);
}

static void	fork_failed(t_all *all, long ind)
{
	long	index;

	index = -1;
	sem_wait(all->mess_sem);
	write_err("Impossible to create a child process");
	while (++index < ind)
		kill(all->pid_philo[index], SIGTERM);
	printf("Simulation is stopped\n");
	sem_post(all->mess_sem);
	return ;
}
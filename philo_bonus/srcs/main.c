#include "../includes/philo_bonus_header.h"

static int	run_program(t_all *all);

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (write_err("You need to input 4 or 5 arguements"), 1);
	all = NULL;
	if (!validate_args(argc, argv))
		return (1);
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
	pid_t	pid;

	ind = -1;
	all->philo->start = get_curr_time();
	all->philo->last_meal = all->philo->start;
	while (++ind < all->num_philos)
	{
		pid = fork();
		if (pid < 0)
		{
			sem_wait(all->mess_sem);
			write_err("Can't create a child process");
			sem_post(all->mess_sem);
			//all.
		}
		else if (pid == 0)
			philo(all, ind);
	}
}

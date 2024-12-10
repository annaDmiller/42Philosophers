#include "../includes/philo_bonus_header.h"

int	validate_args(int argc, char **argv)
{
	int	ind_arg;
	int	ind_car;

	ind_arg = 0;
	while (++ind_arg < argc)
	{
		ind_car = 0;
		while (argv[ind_arg][ind_car])
		{
			if (!ft_isdigit(argv[ind_arg][ind_car]))
				return (write_err("Incorrect input: only digits allowed"),
					0);
			ind_car++;
		}
	}
	return (1);
}

#include "../includes/philo_bonus_header.h"

int	main(int argc, char **argv)
{
	struct s_all	*all;

	if (argc < 5 || argc > 6)
		return (write_err("You need to input 4 or 5 arguements"), 1);
	all = NULL;
	if (!validate_args(argc, argv))
		return (1);
	return (0);
}

#include "../../includes/philo_header.h"

long    ft_atol(const char *nptr)
{
	long	number;
	long	ind;
	long	sign;

	if (!nptr)
		return (0);
	ind = 0;
	number = 0;
	sign = 1;
	while (nptr[ind] == ' ' || (nptr[ind] >= 9 && nptr[ind] <= 13))
		ind++;
	if (nptr[ind] == '-' || nptr[ind] == '+')
		if (nptr[ind++] == '-')
			sign *= -1;
	while (nptr[ind] >= '0' && nptr[ind] <= '9')
	{
		number = 10 * number + nptr[ind] - 48;
		ind++;
	}
	return (sign * number);
}
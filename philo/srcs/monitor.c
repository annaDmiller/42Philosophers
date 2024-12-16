#include "../includes/philo_header.h"

void	*monitor_end(void *arg)
{
	t_all	*all;
    long    ind;

	all = (t_all *) arg;
	while (1)
	{
        ind = -1;
        while (++ind < all->num_philos)
            if (death_checker(&(all->philos[ind])) == 1)
                return (NULL);
	}
	return (NULL);
}

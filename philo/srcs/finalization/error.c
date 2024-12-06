#include "../../includes/philo_header.h"

void    write_err(char *str)
{
    write(2, "Error: [", 8);
    write(2, str, ft_strlen(str));
    write(2, "]\n", 2);
    return ;
}
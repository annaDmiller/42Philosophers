#include "../../includes/philo_header.h"

size_t  ft_strlen(char *str)
{
    size_t  ind;

    if (!str)
        return (0);
    ind = 0;
    while (str[ind])
        ind++;
    return (ind);
}
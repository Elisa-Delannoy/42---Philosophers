#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

int	ft_atoi(const char *nptr);

typedef struct s_philo
{
	pthread_t	threads;
	int			nb_philo;
}	t_philo;


// typedef struct s_var
// {

// }	t_var var;
#endif
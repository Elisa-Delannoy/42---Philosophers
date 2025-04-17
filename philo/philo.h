#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;	
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
	int					last_meal;
	pthread_t			threads;
	size_t				t_init_action;
	struct s_var		*var;
}	t_philo;


typedef struct s_var
{
	int				nb_philo;
	int				t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				nb_eat;
	// size_t			t_init_action;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_var;

// typedef struct s_timeval
// {
// 	time_t		tv_sec;
// 	suseconds_t	tv_usec;
// }	t_timeval;

int	ft_atoi(const char *nptr);

#endif
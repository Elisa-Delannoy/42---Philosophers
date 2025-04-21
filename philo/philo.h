#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_condition
{
	ONLY_ONE_PHILO,
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_condition;

typedef struct s_philo
{
	int					id;
	size_t				last_meal;
	int					total_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			threads;
	size_t				t_init_action;
	struct s_var		*var;
}	t_philo;


typedef struct s_var
{
	int				nb_philo;
	int				nb_meal;
	int				check_dead;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_var;

int	ft_atoi(const char *nptr);

#endif
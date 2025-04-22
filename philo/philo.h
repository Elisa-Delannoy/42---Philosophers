/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:40:06 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/22 16:17:07 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR1 "should be : number_of_philosophers time_to_die time_to_eat "
# define ERROR2 "time_to_sleep [number_of_times_each_philo_must_eat]"

typedef enum e_condition
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_condition;

typedef struct s_philo
{
	int					id;
	long int			last_meal;
	int					total_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			threads;
	struct s_var		*var;
}	t_philo;

typedef struct s_var
{
	int				nb_philo;
	int				nb_meal;
	int				check_dead;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	long int		time_init;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_var;

int		ft_atoi(const char *nptr);
void			*ft_routine(void *arg);
int				ft_check_to_print(t_philo *philo, int c);
long int		ft_get_time(void);
void			sleep_ms(int duration);
int				ft_check_continue(t_var *var);

#endif
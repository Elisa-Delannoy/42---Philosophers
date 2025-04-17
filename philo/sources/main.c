/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/17 18:54:27 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_get_time(void)
{
	struct timeval	tv;
	size_t		time_ms;
	
	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

int	check_philo_is_dead(t_var var)
{
	if (ft_get_time() - var.philo->last_meal > var.t_eat)
		return (0);
	else
		return (1);
}

int	ft_take_fork(t_var var)
{
	if (var.nb_philo == 1)
		return (1);
	else if (var.nb_philo % 2 == 0) /*test later for impair*/
	{
		if (var.philo->id % 2 == 1)
		{
			pthread_mutex_lock(&var.philo->left_fork);
			pthread_mutex_lock(&var.philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(&var.philo->right_fork);
			pthread_mutex_lock(&var.philo->left_fork);
		}
		printf("philo = %d is eating\n", var.philo->id);	
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	
	while(1)
	{
		if (check_philo_is_dead(*philo->var) == 0)
			break;
		if (ft_take_fork(*philo->var) == 1)
			break;
		if (ft_get_time() - philo->t_init_action > philo->var->t_eat)
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&philo->right_fork);
		}
			
	}
	
	// while(ft_get_time() - philo->t_init_action < philo->var->t_eat)
	// 	printf("eat");
	// printf("\n");
	// // usleep(1000000);
	// philo->last_meal = ft_get_time();
	// philo->t_init_action = ft_get_time();
	// // printf("init %zu\n", philo->var->t_init_action);
	// // printf("sleep %zu\n",  philo->var->t_sleep);
	// // printf("diff %zu\n",  ft_get_time() - philo->t_init_action);
	// while(ft_get_time() - philo->t_init_action < philo->var->t_sleep)
	// 	printf("sleep");
	// printf("\n");
	// // printf("think\n");
	return (NULL);
}


void	ft_kill_philosophers(t_var var)
{
	int	i;
	
	i = 0;
	while (i < var.nb_philo)
	{
		if (pthread_join(var.philo[i].threads, NULL) != 0)
			return;
		// printf("philo = %d finished execution\n" ,i + 1);
		i++;
	}
}

void	ft_init_action_philo_and_fork(t_var *var)
{
	size_t	i;

	i = 0;
	while (i < (size_t)var->nb_philo)
	{
		var->philo[i].id = i + 1;
		var->philo[i].right_fork = i; 
		var->philo[i].left_fork = (i + 1) % var->nb_philo;
		var->philo[i].last_meal = 0;
		var->philo[i].t_init_action = ft_get_time();
		var->philo[i].var = var;
		if (pthread_mutex_init(&var->fork[i], NULL) != 0)
			return ;		
		if (pthread_create(&var->philo[i].threads, NULL, &routine, &var->philo[i]) != 0)
			return ;
		i++;
	}
}

t_var	ft_init_action(char **argv)
{
	t_var	var;
	
	var.nb_philo = ft_atoi(argv[1]);
	var.t_die = ft_atoi(argv[2]);
	var.t_eat = ft_atoi(argv[3]);
	var.t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		var.nb_eat = ft_atoi(argv[5]);
	else
		var.nb_eat = -1;
	var.fork = malloc (var.nb_philo * sizeof(pthread_mutex_t));
	var.philo = malloc(var.nb_philo * sizeof(t_philo));
	if (!var.fork || !var.philo)
	{
		var.nb_philo = -1;
		return (var);
	}
	ft_init_action_philo_and_fork(&var);
	return (var);
}

int	main(int argc, char **argv)
{
	t_var	var;
	
	if (argc == 5 || argc == 6)
	{
		var = ft_init_action(argv);
		// if (var.nb_philo == 1)
		// 	return 1;
		ft_kill_philosophers(var);
	}
	else
		return 0;
}

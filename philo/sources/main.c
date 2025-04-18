/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/18 11:43:43 by edelanno         ###   ########.fr       */
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

int	check_philo_is_dead(t_philo philo)
{
	if (ft_get_time() - philo.last_meal > philo.var->t_die)
	{
		printf("%lu %d died\n", ft_get_time(), philo.id);
		return (0);
	}
	else
		return (1);
}

void	ft_sleep_and_think(t_philo philo)
{
	philo.t_init_action = ft_get_time();
	
	printf("%lu %d is sleeping\n", ft_get_time(), philo.id);
	while (ft_get_time() - philo.t_init_action <= philo.var->t_sleep)
		usleep(1);
	if (ft_get_time() - philo.t_init_action > philo.var->t_sleep)
	{
		printf("%lu %d is thinking\n", ft_get_time(), philo.id);
	}
}

void	ft_eat(t_philo philo)
{
	
	printf("%lu %d is eating\n", ft_get_time(), philo.id);
	while (ft_get_time() - philo.t_init_action <= philo.var->t_eat)
		usleep(1);
	if (ft_get_time() - philo.t_init_action > philo.var->t_eat)
	{
		philo.last_meal= ft_get_time();
		if (philo.var->nb_meal != -1)
		{
			philo.total_meal++;
			printf("TOT MEAL EAT %d\n\n", philo.total_meal);
		}
		pthread_mutex_unlock(&philo.left_fork);
		pthread_mutex_unlock(&philo.right_fork);
	}
}

int	ft_take_fork(t_philo philo)
{
	if (philo.var->nb_philo == 1)
	{
		printf("%lu %d has taken a fork\n", ft_get_time(), philo.id);
		printf("%lu %d died\n", ft_get_time(), philo.id);
		return (1);
	}
	// printf("ID TAKE FORK %d\n", philo.id);
	if (philo.id % 2 == 1)
	{
		pthread_mutex_lock(&philo.left_fork);
		printf("%lu %d has taken a fork\n", ft_get_time(), philo.id);
		pthread_mutex_lock(&philo.right_fork);
		printf("%lu %d has taken a fork\n", ft_get_time(), philo.id);
		philo.t_init_action = ft_get_time();
	}
	else
	{
		pthread_mutex_lock(&philo.right_fork);
		printf("%lu %d has taken a fork\n", ft_get_time(), philo.id);
		pthread_mutex_lock(&philo.left_fork);
		printf("%lu %d has taken a fork\n", ft_get_time(), philo.id);
		philo.t_init_action = ft_get_time();
	}	
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	
	while((philo->var->nb_meal == -1 || philo->total_meal <= philo->var->nb_meal))
	{
		// printf("ID ROUTINE %d\n", philo->id);
		if (ft_take_fork(*philo) == 1)	
			break;
		if (check_philo_is_dead(*philo) == 0)
			break;
		ft_eat(*philo);
		if (check_philo_is_dead(*philo) == 0)
			break;
		ft_sleep_and_think(*philo);
		if (check_philo_is_dead(*philo) == 0)
			break;
	}
	return (NULL);
}

void	ft_wait_philosophers(t_var var)
{
	int	i;
	
	i = 0;
	while (i < var.nb_philo)
	{
		if (pthread_join(var.philo[i].threads, NULL) != 0)
			return;
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
		var->philo[i].right_fork = var->fork[i]; 
		var->philo[i].left_fork = var->fork[(i + 1) % var->nb_philo];
		var->philo[i].t_init_action = ft_get_time();
		var->philo[i].last_meal = var->philo[i].t_init_action;
		var->philo[i].total_meal = 0;
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
		var.nb_meal = ft_atoi(argv[5]);
	else
		var.nb_meal = -1;
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
		ft_wait_philosophers(var);
	}
	else
		return 0;
}

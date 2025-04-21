/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/21 12:08:02 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_get_time(void)
{
	struct timeval	tv;
	size_t			time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

int	ft_check_philo_is_dead(t_philo *philo)
{
	if (ft_get_time() - philo->last_meal > philo->var->t_die)
		return (0);
	else
		return (1);
}

void	ft_all_printf(t_philo *philo, int c)
{
	// if (c == 1)
	// 	printf("%lu %d has taken a fork\n", ft_get_time(), philo->id);
	if (c == TAKE_FORK)
		printf("%lu %d has taken a fork\n", ft_get_time(), philo->id);
	else if (c == 3)
		printf("%lu %d is eating\n", ft_get_time(), philo->id);
	else if (c == 4)
		printf("%lu %d is sleeping\n", ft_get_time(), philo->id);
	else if (c  == 5)
		printf("%lu %d is thinking\n", ft_get_time(), philo->id);
}

int	ft_check_to_print(t_philo *philo, int c)
{
	pthread_mutex_lock(&philo->var->print);
	if (philo->var->check_dead != 0)
		ft_all_printf(philo, c);
	pthread_mutex_unlock(&philo->var->print);
	return (0);
}

int	ft_sleep(t_philo *philo)
{	
	if (ft_check_to_print(philo, 4) == 0)
	{
		usleep(philo->var->t_sleep * 1000);
		return (0);
	}	
	else
		return (1);
}

void	ft_eat(t_philo *philo)
{
	ft_check_to_print(philo, 3);
	philo->last_meal= ft_get_time();
	usleep(philo->var->t_eat * 1000);
	// if (philo->var->nb_meal != -1)
	philo->total_meal++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	ft_take_fork(t_philo *philo)
{
	// if (philo->var->nb_philo == 1)
	// {
	// 	ft_check_to_print(philo, 1);
	// 	return (1);
	// }
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_check_to_print(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_check_to_print(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_check_to_print(philo, 2);;
		pthread_mutex_lock(philo->left_fork);
		ft_check_to_print(philo, 2);
	}	
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	
	while (1)
	{
		// pthread_mutex_lock(&philo->var->dead);
		if (philo->var->check_dead == 0)
		{
			printf("check death dans if %d\n\n", philo->var->check_dead);
			// pthread_mutex_unlock(&philo->var->dead);
			break ;
		}
		// pthread_mutex_unlock(&philo->var->dead);
		printf("check death %d\n\n", philo->var->check_dead);
		ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_all_printf(philo, 5);
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
		var->philo[i].right_fork = &var->fork[i]; 
		var->philo[i].left_fork = &var->fork[(i + 1) % var->nb_philo];
		var->philo[i].t_init_action = ft_get_time();
		var->philo[i].last_meal = var->philo[i].t_init_action;
		var->philo[i].total_meal = 0;
		var->philo[i].var = var;
		if (pthread_mutex_init(&var->fork[i], NULL) != 0)
			return ;
	i++;
	}
	i = 0;
	while (i < (size_t)var->nb_philo)
	{
		if (pthread_create(&var->philo[i].threads, NULL, &ft_routine, &var->philo[i]) != 0)
			return ;
		i++;
	}
}

void	ft_init_action(char **argv, t_var *var)
{
	var->nb_philo = ft_atoi(argv[1]);
	var->t_die = ft_atoi(argv[2]);
	var->t_eat = ft_atoi(argv[3]);
	var->t_sleep = ft_atoi(argv[4]);
	var->check_dead = 1;
	if (argv[5])
		var->nb_meal = ft_atoi(argv[5]);
	else
		var->nb_meal = -1;
	if (pthread_mutex_init(&var->print, NULL) != 0
			|| pthread_mutex_init(&var->dead, NULL) != 0)
		return ;
	var->fork = malloc (var->nb_philo * sizeof(pthread_mutex_t));
	var->philo = malloc(var->nb_philo * sizeof(t_philo));
	if (!var->fork || !var->philo)
	{
		free(var->fork);
		free(var->philo);
		var->nb_philo = -1;
		return ;
	}
	ft_init_action_philo_and_fork(var);
	return ;
}

int	ft_check_nb_meal(t_var *var)
{
	int	j;
	
	j = 0;
	while (j < var->nb_philo && var->philo[j].total_meal > var->nb_meal)
		j++;
	if (j == var->nb_philo)
	{
		pthread_mutex_lock(&var->dead);
		var->check_dead = 0;
		pthread_mutex_unlock(&var->dead);
		return (1);
	}
	else
		return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	ft_init_action(argv, &var);
	while (1)
	{
		if (var.nb_meal != -1 && var.philo[i].total_meal > var.nb_meal)
		{
			if (ft_check_nb_meal(&var) == 1)
				break ;
		}
		if (ft_check_philo_is_dead(&var.philo[i]) == 0)
		{
			pthread_mutex_lock(&var.dead);
			var.check_dead = 0;
			pthread_mutex_unlock(&var.dead);
			printf("%lu %d died\n", ft_get_time(), var.philo->id);
			printf("check death main %d\n\n", var.check_dead);
			break ;
		}
		i++;
		if (i % var.nb_philo == 0)
			i = 0;
	}
	ft_wait_philosophers(var);
}

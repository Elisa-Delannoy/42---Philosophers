/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/23 11:57:47 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_wait_philosophers(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		if (pthread_join(var->philo[i].threads, NULL) != 0)
			return ;
		i++;
	}
}

void	ft_init_action_philo_and_fork(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		var->philo[i].id = i + 1;
		var->philo[i].right_fork = &var->fork[i];
		var->philo[i].left_fork = &var->fork[(i + 1) % var->nb_philo];
		var->philo[i].total_meal = 0;
		var->philo[i].last_meal = ft_get_time();
		var->philo[i].var = var;
		if (pthread_mutex_init(&var->fork[i], NULL) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < var->nb_philo)
	{
		if (pthread_create(&var->philo[i].threads, NULL,
				&ft_routine, &var->philo[i]) != 0)
			return ;
		i++;
	}
}

int	ft_init_action(char **argv, t_var *var)
{
	var->nb_philo = ft_atoi(argv[1]);
	var->t_die = ft_atoi(argv[2]);
	var->t_eat = ft_atoi(argv[3]);
	var->t_sleep = ft_atoi(argv[4]);
	var->check_dead = 1;
	if (argv[5])
		var->nb_meal = (int)ft_atoi(argv[5]);
	else
		var->nb_meal = -1;
	if (var->nb_philo == 0 || var->nb_philo == -2 || var->t_die == -2
		|| var->t_eat == -2 || var->t_sleep == -2 || var->nb_meal == -2)
		return (1);
	if (pthread_mutex_init(&var->print, NULL) != 0
		|| pthread_mutex_init(&var->dead, NULL) != 0
		|| pthread_mutex_init(&var->meal, NULL) != 0)
		return (1);
	var->fork = malloc (var->nb_philo * sizeof(pthread_mutex_t));
	var->philo = malloc(var->nb_philo * sizeof(t_philo));
	if (!var->fork || !var->philo)
		return (var->nb_philo = -1, free(var->fork), free(var->philo), 1);
	var->time_init = ft_get_time();
	ft_init_action_philo_and_fork(var);
	return (0);
}

void	ft_quit_clean(t_var *var)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&var->meal);
	pthread_mutex_destroy(&var->print);
	pthread_mutex_destroy(&var->dead);
	while (i < var->nb_philo)
	{
		pthread_mutex_destroy(&var->fork[i]);
		i++;
	}
	free (var->fork);
	free (var->philo);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, ERROR1, 59), write(2, ERROR2, 51), 1);
	if (ft_init_action(argv, &var) == 1)
		return (1);
	if (var.philo->id % 2 == 0)
		ft_sleep_ms(2);
	while (1)
	{
		if (ft_check_continue(&var) != 0)
			break ;
	}
	ft_wait_philosophers(&var);
	ft_quit_clean(&var);
	return (0);
}

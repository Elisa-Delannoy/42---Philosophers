/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:56:29 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/22 15:06:40 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_philo_is_dead(t_philo *philo)
{
	int	temp;
	
	pthread_mutex_lock(&philo->var->meal);
	temp = philo->last_meal;
	pthread_mutex_unlock(&philo->var->meal);
	if (ft_get_time() - temp > philo->var->t_die)
		return (0);
	else
		return (1);
}

// int	ft_check_nb_meal(t_var *var)
// {
// 	int	j;
// 	int	temp;
	
// 	j = 0;
// 	pthread_mutex_lock(&var->meal);
// 	temp = var->philo[j].total_meal;
// 	pthread_mutex_unlock(&var->meal);
	
// 	while (j < var->nb_philo && temp >= var->nb_meal)
// 		j++;
// 	if (j == var->nb_philo)
// 	{
// 		pthread_mutex_lock(&var->dead);
// 		var->check_dead = 0;
// 		pthread_mutex_unlock(&var->dead);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

void	ft_check(t_var *var)
{
	int	temp_nb_meal;
	int	temp_last_meal;
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_lock(&var->meal);
		temp_nb_meal = var->philo[i].total_meal;
		temp_last_meal = philo->last_meal;
		pthread_mutex_lock(&var->meal);
		if (var->nb_meal != -1 && temp_nb_meal >= var->nb_meal)
			count++;
		if (count == var->nb_philo)
		{
			pthread_mutex_lock(&var->dead);
			var->check_dead = 0;
			pthread_mutex_unlock(&var->dead);
			return (1);
		}
		if (ft_check_philo_is_dead(&var.philo[i]) == 0)
		{
			ft_check_to_print(var.philo, DIED);
			break ;
		}


		int	ft_check_philo_is_dead(t_philo *philo)
{
	int	temp;
	
	pthread_mutex_lock(&philo->var->meal);
	temp = philo->last_meal;
	pthread_mutex_unlock(&philo->var->meal);
	if (ft_get_time() - temp > philo->var->t_die)
		return (0);
	else
		return (1);
}
		// i++;
		if (++i % var.nb_philo == 0)
			i = 0;
	}
}

int	ft_check_to_print(t_philo *philo, int c)
{
	int	time;

	time = ft_get_time() - philo->var->time_init;
	pthread_mutex_lock(&philo->var->dead);
	pthread_mutex_lock(&philo->var->print);
	if (philo->var->check_dead != 0)
	{
		if (c == TAKE_FORK)
			printf("%lu %d has taken a fork\n", time, philo->id);
		else if (c == EATING)
			printf("%lu %d is eating\n", time, philo->id);
		else if (c == SLEEPING)
			printf("%lu %d is sleeping\n", time, philo->id);
		else if (c == THINKING)
			printf("%lu %d is thinking\n", time, philo->id);
		else if (c == DIED)
		{
			philo->var->check_dead = 0;
			printf("%lu %d died\n", ft_get_time() - philo->var->time_init, philo->var->philo->id);
		}
	}
	// printf("temps simu %ld\n", ft_get_time() - philo->var->time_init - philo->var->delta_time_init) ;
	// printf("last meal %ld\n", philo->last_meal - philo->var->delta_time_init);
	// printf("simu - last meal %ld\n\n", ft_get_time() - philo->var->time_init - philo->last_meal - philo->var->delta_time_init);
	// pthread_mutex_unlock(&philo->var->meal);
	pthread_mutex_unlock(&philo->var->print);
	pthread_mutex_unlock(&philo->var->dead);
	return (0);
}

// void	ft_dead_in_main(t_var *var)
// {
// 	pthread_mutex_lock(&var->dead);
// 	var->check_dead = 0;
// 	pthread_mutex_unlock(&var->dead);
// 	printf("%lu %d died\n", ft_get_time() - var->time_init, var->philo->id);
// }

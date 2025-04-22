/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:56:29 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/22 11:29:02 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_philo_is_dead(t_philo *philo)
{
	int	time_without_meal;

	pthread_mutex_lock(&philo->var->meal);
	time_without_meal = ft_get_time() - philo->var->time_init - philo->last_meal;
	pthread_mutex_unlock(&philo->var->meal);
	// pthread_mutex_lock(&philo->var->print);
	// printf("temps simu %ld\n\n", ft_get_time() - philo->var->time_init);
	// printf("last meal %ld\n\n", philo->last_meal);
	// printf("simu - last meal %ld\n\n", ft_get_time() - philo->var->time_init - philo->last_meal);
	// pthread_mutex_unlock(&philo->var->print);
	// pthread_mutex_lock(&philo->var->meal);
	if (time_without_meal > philo->var->t_die)
		return (0);
	else
		return (1);
}

int	ft_check_nb_meal(t_var *var)
{
	int	j;

	j = 0;
	while (j < var->nb_philo && var->philo[j].total_meal >= var->nb_meal)
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

int	ft_check_to_print(t_philo *philo, int c)
{
	pthread_mutex_lock(&philo->var->dead);
	pthread_mutex_lock(&philo->var->print);
	if (philo->var->check_dead != 0)
	{
		if (c == TAKE_FORK)
			printf("%lu %d has taken a fork\n", ft_get_time() - philo->var->time_init, philo->id);
		else if (c == EATING)
			printf("%lu %d is eating\n", ft_get_time() - philo->var->time_init, philo->id);
		else if (c == SLEEPING)
			printf("%lu %d is sleeping\n", ft_get_time() - philo->var->time_init, philo->id);
		else if (c == THINKING)
			printf("%lu %d is thinking\n", ft_get_time() - philo->var->time_init, philo->id);
		else if (c == DIED)
		{
			philo->var->check_dead = 0;
			printf("%lu %d died\n", ft_get_time() - philo->var->time_init, philo->var->philo->id);
		}
	}
	// if ()
	printf("temps simu %ld\n", ft_get_time() - philo->var->time_init);
	printf("last meal %ld\n", philo->last_meal);
	printf("simu - last meal %ld\n\n", ft_get_time() - philo->var->time_init - philo->last_meal);
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

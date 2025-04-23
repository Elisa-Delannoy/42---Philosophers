/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:56:29 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/23 11:38:25 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_dead(t_var *var, int count)
{
	pthread_mutex_lock(&var->dead);
	var->check_dead = 0;
	pthread_mutex_unlock(&var->dead);
	if (count == var->nb_philo)
		return (1);
	else
		return (ft_check_to_print(var->philo, DIED), 2);
}

int	ft_check_continue(t_var *var)
{
	int			temp_nb_meal;
	long int	temp_last_meal;
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_lock(&var->meal);
		temp_nb_meal = var->philo[i].total_meal;
		temp_last_meal = var->philo[i].last_meal;
		pthread_mutex_unlock(&var->meal);
		if (var->nb_meal != -1 && temp_nb_meal >= var->nb_meal)
			count++;
		if (count == var->nb_philo
			|| (ft_get_time() - temp_last_meal > (long int)var->t_die))
			return (ft_is_dead(var, count));
		i++;
		usleep(1000);
	}
	return (0);
}

int	ft_check_to_print(t_philo *philo, int c)
{
	long int	time;

	time = ft_get_time() - philo->var->time_init;
	pthread_mutex_lock(&philo->var->print);
	pthread_mutex_lock(&philo->var->dead);
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
	}
	if (c == DIED)
		printf("%lu %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->var->dead);
	pthread_mutex_unlock(&philo->var->print);
	return (0);
}

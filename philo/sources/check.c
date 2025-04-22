/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:56:29 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/22 16:15:35 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	ft_check_philo_is_dead(t_philo *philo)
// {
// 	int	temp;
	
// 	pthread_mutex_lock(&philo->var->meal);
// 	temp = philo->last_meal;
// 	pthread_mutex_unlock(&philo->var->meal);
// 	if (ft_get_time() - temp > philo->var->t_die)
// 		return (0);
// 	else
// 		return (1);
// }

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
	long int	tmp_lst_meal;
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_lock(&var->meal);
		temp_nb_meal = var->philo[i].total_meal;
		tmp_lst_meal = var->philo[i].last_meal;
		pthread_mutex_unlock(&var->meal);
		if (var->nb_meal != -1 && temp_nb_meal >= var->nb_meal)
			count++;
		if (count == var->nb_philo || (ft_get_time() - tmp_lst_meal > var->t_die))
			return(ft_is_dead(var, count));
		i++;
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
		else if (c == DIED)
			printf("%lu %d died\n", time, philo->id);
	}
	// printf("temps simu %ld\n", ft_get_time() - philo->var->time_init - philo->var->delta_time_init) ;
	// printf("last meal %ld\n", philo->last_meal - philo->var->delta_time_init);
	// printf("simu - last meal %ld\n\n", ft_get_time() - philo->var->time_init - philo->last_meal - philo->var->delta_time_init);
	// pthread_mutex_unlock(&philo->var->meal);
	pthread_mutex_unlock(&philo->var->dead);
	pthread_mutex_unlock(&philo->var->print);
	return (0);
}

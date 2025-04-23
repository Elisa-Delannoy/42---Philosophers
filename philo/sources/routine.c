/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:45:19 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/23 11:29:19 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_sleep(t_philo *philo)
{
	if (ft_check_to_print(philo, SLEEPING) == 0)
	{
		ft_sleep_ms(philo->var->t_sleep);
		return (0);
	}
	else
		return (1);
}

void	ft_eat(t_philo *philo)
{
	ft_check_to_print(philo, EATING);
	pthread_mutex_lock(&philo->var->meal);
	philo->last_meal = ft_get_time();
	philo->total_meal++;
	pthread_mutex_unlock(&philo->var->meal);
	ft_sleep_ms(philo->var->t_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	ft_take_fork(t_philo *philo)
{
	if (philo->var->nb_philo == 1)
	{
		ft_check_to_print(philo, TAKE_FORK);
		return (1);
	}
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
		ft_check_to_print(philo, TAKE_FORK);
		pthread_mutex_lock(philo->left_fork);
		ft_check_to_print(philo, TAKE_FORK);
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->var->dead);
		if (philo->var->check_dead == 0)
		{
			pthread_mutex_unlock(&philo->var->dead);
			break ;
		}
		pthread_mutex_unlock(&philo->var->dead);
		if (ft_take_fork(philo) == 1)
			return (NULL);
		ft_eat(philo);
		ft_sleep(philo);
		ft_check_to_print(philo, THINKING);
	}
	return (NULL);
}

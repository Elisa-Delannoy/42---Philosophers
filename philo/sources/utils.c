/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:36:43 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/18 12:06:21 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;
	int	m;

	nb = 0;
	i = 0;
	m = 1;
	if ((nptr[i] < '0' && nptr[i] > '9') && nptr[i] != '+' && nptr[i] != '-')
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = -m;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * m);
}

// void	ft_sleep_and_think(t_philo philo)
// {
// 	philo.t_init_action = ft_get_time();
	
// 	printf("%lu %d is sleeping\n", ft_get_time(), philo.id);
// 	// while (ft_get_time() - philo.t_init_action <= philo.var->t_sleep)
// 	usleep(philo.var->t_sleep * 1000);
// 	// if (ft_get_time() - philo.t_init_action > philo.var->t_sleep)
// 	// {
// 	printf("%lu %d is thinking\n", ft_get_time(), philo.id);
// 	// }
// }

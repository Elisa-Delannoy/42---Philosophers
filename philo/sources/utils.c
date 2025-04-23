/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:36:43 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/23 10:29:37 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleep_ms(int sleeping_time)
{
	long int	start;

	start = ft_get_time();
	while (ft_get_time() < start + sleeping_time)
		usleep(500);
}

long int	ft_get_time(void)
{
	struct timeval	tv;
	long int		time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_ms);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	if ((nptr[i] < '0' && nptr[i] > '9') && nptr[i] != '+' && nptr[i] != '-')
		return (-1);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	if (nptr[i] != '\0' || nb - 2147483647 > 0)
		return (-2);
	return (nb);
}

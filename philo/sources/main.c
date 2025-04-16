/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:06:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/04/16 15:28:48 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine()
{
	// printf("test\n");
	return (NULL);
}

void	ft_take_fork(t_philo philo, int i)
{
	if (philo.nb_philo % 2 == 0)
	{
		if (i % 2 == 0)
			printf("philo = %d is eating\n" ,i);
	}
}

void	ft_create_philosphers(t_philo philo)
{
	int			i;

	i = 0;
	while (i < philo.nb_philo)
	{
		if (pthread_create(philo.threads + i, NULL, &routine, NULL) != 0)
			return;
		ft_take_fork(philo, i + 1);
		// printf("philo = %d is created\n" , i + 1);
		i++;
	}
}

void	ft_kill_philosophers(t_philo philo)
{
	int	i;
	
	i = 1;
	while (i <= philo.nb_philo)
	{
		if (pthread_join(philo.threads[i - 1], NULL) != 0)
			return;
		// printf("philo = %d finished execution\n" ,i);
		i++;
	}
}

t_philo	ft_init(char **argv)
{
	t_philo	philo;
	
	philo.nb_philo = ft_atoi(argv[1]);
	philo.threads = malloc(philo.nb_philo * sizeof(pthread_t));
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	if (argc == 4 || argc == 5)
	{
		philo = ft_init(argv);
		if (philo.nb_philo == 1)
			return 1;
		ft_create_philosphers(philo);
		ft_kill_philosophers(philo);
	}
	else
		return 0;
}

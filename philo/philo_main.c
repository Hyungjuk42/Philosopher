/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:49:03 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 17:24:32 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher(t_philo *philo)
{
	int	i;
	int	ret;

	i = 0;
	if (pthread_mutex_lock(&(philo->mat->open_restaurant)) != 0)
		return (0);
	while (i < philo->mat->number_of_philosophers)
	{
		if (pthread_create(&(philo[i].thread), NULL, philo_run, &philo[i]) != 0)
		{
			make_dead(philo->mat);
			if (pthread_mutex_unlock(&(philo->mat->open_restaurant)) != 0)
				return (0);
			while (i > 0)
			{
				i --;
				pthread_join(philo[i].thread, (void **) &ret);
			}
			free_all(philo, philo->mat);
			return (0);
		}
		i ++;
	}
	return (1);
}

int	open_and_close_restaurant(t_philo *philo)
{
	int	i;

	i = 0;
	gettimeofday(&(philo->mat->open_time), NULL);
	if (pthread_mutex_unlock(&(philo->mat->open_restaurant)) != 0)
		return (0);
	usleep(200);
	monitoring_philosopher(philo, philo->mat);
	while (i < philo->mat->number_of_philosophers)
	{
		pthread_join(philo[i].thread, NULL);
		i ++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong INPUT\n");
		return (1);
	}
	philo = set_philosopher(ac, av);
	if (philo == NULL)
		return (1);
	if (philo->mat->repeat_number == 0 || \
		(philo->mat->repeat_number == -1 && ac == 6))
	{
		free_all(philo, philo->mat);
		return (1);
	}
	pthread_mutex_init(&philo->mat->dead_lock, NULL);
	pthread_mutex_init(&philo->mat->full_lock, NULL);
	pthread_mutex_init(&philo->mat->time_lock, NULL);
	if (create_philosopher(philo) == 0)
		return (1);
	open_and_close_restaurant(philo);
	free_all(philo, philo->mat);
}

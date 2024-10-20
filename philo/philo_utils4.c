/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:46:55 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 17:20:16 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full_mutex(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->mat->dead_lock);
	if (philo->is_full == flag)
	{
		pthread_mutex_unlock(&philo->mat->dead_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->mat->dead_lock);
		return (0);
	}
}

void	make_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->mat->dead_lock);
	philo->is_full = 1;
	pthread_mutex_unlock(&philo->mat->dead_lock);
}

int	ft_min_max(int a, int b, int flag, int philo_num)
{
	if ((flag + philo_num) % 2 == 0)
	{
		return (b);
	}
	else
	{
		return (a);
	}
}

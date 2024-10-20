/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:20:57 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_mutex(t_mat *mat, int flag)
{
	pthread_mutex_lock(&mat->dead_lock);
	if (mat->is_dead == flag)
	{
		pthread_mutex_unlock(&mat->dead_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&mat->dead_lock);
		return (0);
	}
}

void	make_dead(t_mat *mat)
{
	pthread_mutex_lock(&mat->dead_lock);
	mat->is_dead = 1;
	pthread_mutex_unlock(&mat->dead_lock);
}

int	chk_philo_dead(t_philo *philo, t_mat *mat, struct timeval *cur_t, int i)
{
	int	diff_time;
	int	dead_time;

	diff_time = time_mutex(&philo[i], mat, cur_t);
	if (is_dead_mutex(mat, 0) && diff_time >= mat->time_to_die && \
		is_full_mutex(philo, 1) == 0)
	{
		make_dead(mat);
		dead_time = convert_to_ms(&(mat->open_time), cur_t);
		pthread_mutex_lock(&mat->print_lock);
		printf("%d %d died\n", dead_time, \
		philo[i].philo_num + 1);
		pthread_mutex_unlock(&mat->print_lock);
		return (0);
	}
	else if (is_dead_mutex(mat, 1) || \
		full_mutex(mat, mat->number_of_philosophers))
		return (0);
	return (1);
}

void	monitoring_philosopher(t_philo *philo, t_mat *mat)
{
	int				i;
	int				res;
	int				num_of_philos;
	struct timeval	cur_time;

	num_of_philos = mat->number_of_philosophers;
	while ((is_dead_mutex(mat, 0)) && !full_mutex(mat, num_of_philos))
	{
		i = 0;
		while (i < mat->number_of_philosophers)
		{
			if (gettimeofday(&cur_time, NULL) != 0)
			{
				make_dead(mat);
				return ;
			}
			res = chk_philo_dead(philo, mat, &cur_time, i);
			if (res == 0)
				return ;
			i ++;
		}
		usleep(100);
	}
}

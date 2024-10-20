/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:21:34 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_to_ms(struct timeval *s, struct timeval *e)
{
	return ((e->tv_sec - s->tv_sec) * 1000 + (e->tv_usec - s->tv_usec) / 1000);
}

void	get_sleep(t_mat *mat, struct timeval *s, int time)
{
	int				i;
	struct timeval	cur_time;

	i = 0;
	gettimeofday(&cur_time, NULL);
	while (convert_to_ms(s, &cur_time) < time)
	{
		if (is_dead_mutex(mat, 1))
			return ;
		usleep(50);
		gettimeofday(&cur_time, NULL);
	}
}

int	printf_m(char *s, t_philo *philo, t_mat *mat)
{
	struct timeval	cur_time;

	if (pthread_mutex_lock(&(mat->print_lock)) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	if (gettimeofday(&cur_time, NULL) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	philo->passed_time = convert_to_ms(&(mat->open_time), &cur_time);
	if (is_dead_mutex(mat, 0))
		printf(s, philo->passed_time, philo->philo_num + 1);
	if (pthread_mutex_unlock(&(mat->print_lock)) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	if (is_dead_mutex(mat, 1))
		return (0);
	return (1);
}

int	philosopher_fork_lock(t_philo *philo, t_mat *mat)
{
	if (pthread_mutex_lock(&(mat->fork_mat[philo->fork1])) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	printf_m("%d %d has taken a fork\n", philo, mat);
	if (pthread_mutex_lock(&(mat->fork_mat[philo->fork2])) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	printf_m("%d %d has taken a fork\n", philo, mat);
	return (1);
}

int	philosopher_fork_unlock(t_philo *philo, t_mat *mat)
{
	if (pthread_mutex_unlock(&(mat->fork_mat[philo->fork1])) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	if (pthread_mutex_unlock(&(mat->fork_mat[philo->fork2])) != 0)
	{
		make_dead(mat);
		return (ERROR);
	}
	return (1);
}

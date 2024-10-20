/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:56:27 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 16:39:28 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	num;
	long long	sign;
	int			idx;

	num = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str ++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str ++;
	while ('0' == *str)
		str ++;
	idx = 0;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		num *= 10;
		num += str[idx] - '0';
		idx ++;
	}
	num *= sign;
	if (idx > 11 || num < INT_MIN || num > MAX || str[idx] != 0)
		return (-10);
	return ((int)num);
}

int	full_mutex(t_mat *mat, int flag)
{
	pthread_mutex_lock(&mat->full_lock);
	if (mat->full_philo == flag)
	{
		pthread_mutex_unlock(&mat->full_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&mat->full_lock);
		return (0);
	}
}

void	increase_full(t_mat *mat)
{
	pthread_mutex_lock(&mat->full_lock);
	mat->full_philo += 1;
	pthread_mutex_unlock(&mat->full_lock);
}

int	time_mutex(t_philo *philo, t_mat *mat, struct timeval *cur_t)
{
	int	tmp;

	pthread_mutex_lock(&mat->time_lock);
	tmp = convert_to_ms(&(philo->cur_time), cur_t);
	pthread_mutex_unlock(&mat->time_lock);
	return (tmp);
}

void	refresh_time(t_philo *philo, t_mat *mat)
{
	pthread_mutex_lock(&mat->time_lock);
	if (gettimeofday(&(philo->cur_time), NULL) != 0)
	{
		make_dead(mat);
	}
	pthread_mutex_unlock(&mat->time_lock);
}

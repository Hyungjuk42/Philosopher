/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:24:36 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_eating_food(t_philo *philo, t_mat *mat)
{
	if (is_dead_mutex(mat, 1) || full_mutex(mat, mat->number_of_philosophers))
	{
		make_dead(mat);
		philosopher_fork_unlock(philo, mat);
		return (0);
	}
	refresh_time(philo, mat);
	printf_m("%d %d is eating\n", philo, mat);
	philo->repeat_time += 1;
	get_sleep(mat, &(mat->open_time), philo->passed_time + mat->time_to_eat);
	if (mat->repeat_number != -1 && philo->repeat_time == mat->repeat_number)
	{
		increase_full(mat);
		philosopher_fork_unlock(philo, mat);
		make_full(philo);
		return (0);
	}
	return (1);
}

int	philosopher_sleeping_and_thinking(t_philo *philo, t_mat *mat)
{
	if (is_dead_mutex(mat, 1) || full_mutex(mat, mat->number_of_philosophers))
	{
		make_dead(mat);
		return (0);
	}
	printf_m("%d %d is sleeping\n", philo, mat);
	get_sleep(mat, &(mat->open_time), philo->passed_time + mat->time_to_sleep);
	printf_m("%d %d is thinking\n", philo, mat);
	usleep(200);
	return (1);
}

void	philo_act(t_philo *philo, t_mat *mat)
{
	while (1)
	{
		if (philosopher_fork_lock(philo, mat) == 0)
			return ;
		if (philosopher_eating_food(philo, mat) == 0)
			return ;
		if (philosopher_fork_unlock(philo, mat) == 0)
			return ;
		if (philosopher_sleeping_and_thinking(philo, mat) == 0)
			return ;
	}
}

void	*philo_run(void *p_info)
{
	t_philo			*philo;
	t_mat			*mat;

	philo = (t_philo *) p_info;
	mat = philo->mat;
	refresh_time(philo, mat);
	if (pthread_mutex_lock(&(mat->open_restaurant)) != 0)
		return (NULL);
	if (pthread_mutex_unlock(&(mat->open_restaurant)) != 0)
		return (NULL);
	refresh_time(philo, mat);
	philo_act(philo, mat);
	return (NULL);
}

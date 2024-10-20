/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:06:57 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*get_time(void *arg)
{
	t_sema	*sema;
	t_mat	*mat;
	t_philo	*philo;

	philo = (t_philo *)arg;
	mat = philo->mat;
	sema = philo->sema;
	while (1)
	{
		sem_wait(philo->loop_lock);
		if (is_dead_mutex(philo) == DIE)
			return (NULL);
		refresh_time(sema, &philo->eat_time, TIME);
		philo->repeat_time += 1;
		if (mat->repeat_num != -1 && philo->repeat_time == mat->repeat_num)
		{
			make_dead(philo, FULL);
			return (NULL);
		}
	}
}

void	after_dead(t_philo *philo)
{
	int				i;
	int				diff;
	struct timeval	cur_time;

	sem_wait(philo->sema->dead_lock);
	if (is_dead_mutex(philo) == LIVE)
	{
		sem_wait(philo->sema->print_lock);
		make_dead(philo, DIE);
		i = -1;
		sem_post(philo->sema->chk_is_dead);
		while (++ i < philo->mat->num_of_philo)
			sem_post(philo->first_philo[i].loop_lock);
		sem_post(philo->sema->time_lock);
		gettimeofday(&cur_time, NULL);
		diff = convert_to_ms(philo->sema, &philo->mat->open_time, &cur_time);
		philo->passed_time = diff;
		printf("%d %d died\n", philo->passed_time, \
		philo->philo_num + 1);
	}
	sem_post(philo->sema->dead_lock);
}

void	*chk_dead(void *arg)
{
	t_philo			*philo;
	struct timeval	cur_time;
	int				diff;

	philo = (t_philo *)arg;
	sem_wait(philo->sema->open_lock);
	sem_post(philo->sema->open_lock);
	gettimeofday(&cur_time, NULL);
	diff = convert_to_ms(philo->sema, &philo->eat_time, &cur_time);
	while (diff < philo->mat->time_to_die)
	{
		if (is_dead_mutex(philo) == DIE || is_dead_mutex(philo) == FULL)
		{
			sem_post(philo->loop_lock);
			return (NULL);
		}
		usleep(100);
		gettimeofday(&cur_time, NULL);
		diff = convert_to_ms(philo->sema, &philo->eat_time, &cur_time);
	}
	after_dead(philo);
	return (NULL);
}

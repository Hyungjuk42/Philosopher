/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:33:44 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_sleep(t_philo *philo, struct timeval *s, int time)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	while (convert_to_ms(philo->sema, s, &cur_time) < time)
	{
		usleep(100);
		if (is_dead_mutex(philo) == DIE)
			return (DIE);
		gettimeofday(&cur_time, NULL);
	}
	return (LIVE);
}

int	philosopher_fork_lock(t_philo *philo, t_sema *sema)
{
	if (sem_wait(sema->fork_con) != SUCCESS)
	{
		return (ERROR);
	}
	if (sem_wait(sema->fork) != SUCCESS)
	{
		sem_post(sema->fork_con);
		return (ERROR);
	}
	printf_m("%d %d has taken a fork\n", philo);
	if (sem_wait(sema->fork) != SUCCESS)
	{
		sem_post(sema->fork_con);
		return (ERROR);
	}
	printf_m("%d %d has taken a fork\n", philo);
	if (sem_post(sema->fork_con) != SUCCESS)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

int	philosopher_fork_unlock(t_sema *sema)
{
	if (sem_post(sema->fork) != SUCCESS)
	{
		return (ERROR);
	}
	if (sem_post(sema->fork) != SUCCESS)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

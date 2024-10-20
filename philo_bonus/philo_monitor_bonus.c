/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:36:43 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:48 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead_mutex(t_philo *philo)
{
	int	res;

	sem_wait(philo->sema->chk_is_dead);
	res = philo->mat->is_dead;
	if (philo->state == FULL)
		res = FULL;
	sem_post(philo->sema->chk_is_dead);
	return (res);
}

void	make_dead(t_philo *philo, int flag)
{
	sem_wait(philo->sema->chk_is_dead);
	if (flag == DIE)
		philo->mat->is_dead = 1;
	philo->state = flag;
	sem_post(philo->sema->chk_is_dead);
}

t_mat	*only_one(t_mat *mat)
{
	printf("%d 1 has taken a fork\n", 0);
	usleep(1000 * mat->time_to_die);
	printf("%d 1 is dead\n", mat->time_to_die);
	return (NULL);
}

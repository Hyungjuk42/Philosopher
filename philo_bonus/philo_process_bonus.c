/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:24:36 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:21 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	printf_m(char *s, t_philo *philo)
{
	struct timeval	cur_time;
	int				diff_time;

	if (sem_wait(philo->sema->print_lock) != SUCCESS)
		return (ERROR);
	if (gettimeofday(&cur_time, NULL) != SUCCESS)
		return (ERROR);
	diff_time = convert_to_ms(philo->sema, &philo->mat->open_time, &cur_time);
	philo->passed_time = diff_time;
	printf(s, philo->passed_time, philo->philo_num + 1);
	if (sem_post(philo->sema->print_lock) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	philosopher_eating_food(t_philo *philo, t_mat *mat, t_sema *sema)
{
	int	target_time;
	int	i;

	i = 0;
	printf_m("%d %d is eating\n", philo);
	sem_post(philo->loop_lock);
	target_time = philo->passed_time + mat->time_to_eat;
	if (get_sleep(philo, &mat->open_time, target_time) == DIE)
	{
		philosopher_fork_unlock(sema);
		return (DIE);
	}
	return (SUCCESS);
}

int	philosopher_sleeping_and_thinking(t_philo *philo, t_mat *mat)
{
	int	target_time;

	printf_m("%d %d is sleeping\n", philo);
	target_time = philo->passed_time + mat->time_to_sleep;
	if (get_sleep(philo, &mat->open_time, target_time) == DIE)
	{
		sem_post(philo->loop_lock);
		return (DIE);
	}
	printf_m("%d %d is thinking\n", philo);
	usleep(200);
	return (SUCCESS);
}

int	philo_act(t_philo *philo)
{
	while (1)
	{
		if (philosopher_fork_lock(philo, philo->sema) == ERROR)
			return (ERROR);
		if (philosopher_eating_food(philo, philo->mat, philo->sema) == ERROR)
			return (ERROR);
		if (philosopher_fork_unlock(philo->sema) == ERROR)
			return (ERROR);
		if (philosopher_sleeping_and_thinking(philo, philo->mat) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	philo_run(t_philo *philo)
{
	t_sema			*sema;

	sema = philo->sema;
	sem_wait(sema->open_lock);
	sem_post(sema->open_lock);
	if (philo_act(philo) == ERROR)
		exit(ERROR);
	exit(SUCCESS);
}

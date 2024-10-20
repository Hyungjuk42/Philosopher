/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:56:27 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 21:04:39 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	convert_to_ms(t_sema *sema, struct timeval *s, struct timeval *e)
{
	int	ret;

	sem_wait(sema->time_lock);
	ret = (e->tv_sec - s->tv_sec) * 1000 + (e->tv_usec - s->tv_usec) / 1000;
	sem_post(sema->time_lock);
	return (ret);
}

void	set_sema_unlink(int num_of_philo)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	while (i < num_of_philo)
	{
		tmp = ft_itoa(i);
		str = ft_strjoin("loop_lock", tmp);
		sem_unlink(str);
		free(str);
		free(tmp);
		i ++;
	}
	sem_unlink("fork");
	sem_unlink("fork_con");
	sem_unlink("print_lock");
	sem_unlink("death_wait");
	sem_unlink("time_lock");
	sem_unlink("chk_is_dead");
	sem_unlink("dead_lock");
	sem_unlink("open_lock");
}

int	refresh_time(t_sema *sema, struct timeval *t_val, int flag)
{
	int	res;

	res = SUCCESS;
	if (flag == TIME)
		sem_wait(sema->time_lock);
	if (gettimeofday(t_val, NULL) == FAIL)
		res = FAIL;
	if (flag == TIME)
		sem_post(sema->time_lock);
	return (res);
}

void	close_all(t_philo *philo, t_sema *sema, int i)
{
	if (philo != NULL)
	{
		while (i < philo->mat->num_of_philo)
		{
			if (philo[i].loop_lock != NULL)
				sem_close(philo[i].loop_lock);
			i ++;
		}
	}
	if (sema == NULL)
		return ;
	if (sema->fork_con != NULL)
		sem_close(sema->fork_con);
	if (sema->fork != NULL)
		sem_close(sema->fork);
	if (sema->print_lock != NULL)
		sem_close(sema->print_lock);
	if (sema->time_lock != NULL)
		sem_close(sema->time_lock);
	if (sema->open_lock != NULL)
		sem_close(sema->open_lock);
	if (sema->chk_is_dead != NULL)
		sem_close(sema->chk_is_dead);
}

void	free_all(t_philo *philo, t_mat *mat, t_sema *sema)
{
	if (mat != NULL)
	{
		if (mat->pid_arr != NULL)
			free(mat->pid_arr);
		free(mat);
	}
	if (sema != NULL)
		free(sema);
	if (philo != NULL)
		free(philo);
}

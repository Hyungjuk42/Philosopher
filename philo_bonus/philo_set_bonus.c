/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:29:52 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 21:07:24 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_mat	*set_philo_material(int ac, char **av)
{
	t_mat	*mat;

	mat = (t_mat *)malloc(sizeof(t_mat));
	if (mat == NULL)
		return (NULL);
	mat->num_of_philo = ft_atoi(av[1]);
	mat->time_to_die = ft_atoi(av[2]);
	mat->time_to_eat = ft_atoi(av[3]);
	mat->time_to_sleep = ft_atoi(av[4]);
	mat->is_dead = 0;
	mat->repeat_num = -1;
	if (ac == 6)
		mat->repeat_num = ft_atoi(av[5]);
	if (mat->num_of_philo < 1 || mat->time_to_die < 0 || mat->time_to_eat < 0 \
		|| mat->time_to_sleep < 0 || (mat->repeat_num <= 0 && ac == 6))
	{
		free(mat);
		return (NULL);
	}
	if (mat->num_of_philo == 1)
	{
		return (only_one(mat));
		free(mat);
	}
	return (mat);
}

t_sema	*set_philo_semaphore(int num_of_philo)
{
	t_sema	*sema;

	sema = (t_sema *)malloc(sizeof(t_sema));
	if (sema == NULL)
		return (NULL);
	if (memset(sema, 0, sizeof(t_sema)) == NULL)
	{
		free(sema);
		return (NULL);
	}
	sema->fork = sem_open("fork", O_CREAT, 777, num_of_philo);
	sema->fork_con = sem_open("fork_con", O_CREAT, 777, 1);
	sema->print_lock = sem_open("print_lock", O_CREAT, 777, 1);
	sema->time_lock = sem_open("time_lock", O_CREAT, 777, 1);
	sema->chk_is_dead = sem_open("chk_is_dead", O_CREAT, 777, 1);
	sema->dead_lock = sem_open("dead_lock", O_CREAT, 777, 1);
	sema->open_lock = sem_open("open_lock", O_CREAT, 777, 1);
	if (sema->fork && sema->fork_con && sema->print_lock && sema->time_lock && \
		sema->chk_is_dead && sema->dead_lock && sema->open_lock)
		return (sema);
	free(sema);
	return (NULL);
}

int	set_each_philo(t_philo *philo, t_mat *mat, t_sema *sema, int i)
{
	char	*tmp;
	char	*str;

	tmp = ft_itoa(i);
	str = ft_strjoin("loop_lock", tmp);
	philo->loop_lock = sem_open(str, O_CREAT, 777, 0);
	free(tmp);
	free(str);
	if (philo->loop_lock == NULL)
	{
		free(philo);
		return (FAIL);
	}
	philo->mat = mat;
	philo->sema = sema;
	philo->repeat_time = 0;
	philo->philo_num = i;
	philo->state = 0;
	return (SUCCESS);
}

t_philo	*set_philo_philosopher(t_mat *mat, t_sema *sema, int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * mat->num_of_philo);
	if (philo == NULL)
		return (NULL);
	if (memset(philo, 0, sizeof(t_philo) * mat->num_of_philo) == NULL)
	{
		free(philo);
		return (NULL);
	}
	mat->pid_arr = (pid_t *)malloc(sizeof(pid_t) * mat->num_of_philo);
	if (mat->pid_arr == NULL)
	{
		free(philo);
		return (NULL);
	}
	while (i < mat->num_of_philo)
	{
		if (set_each_philo(&philo[i], mat, sema, i) == FAIL)
			return (NULL);
		philo[i].first_philo = philo;
		i ++;
	}
	return (philo);
}

t_philo	*set_philosopher(int ac, char **av)
{
	t_mat	*mat;
	t_sema	*sema;
	t_philo	*philo;

	set_sema_unlink(ft_atoi(av[1]));
	mat = set_philo_material(ac, av);
	if (!mat || mat->num_of_philo <= 1 || mat->time_to_die < 0 || \
	mat->time_to_eat < 0 || mat->time_to_sleep < 0 || mat->repeat_num < -1)
		return (NULL);
	sema = set_philo_semaphore(mat->num_of_philo);
	if (mat == NULL || sema == NULL)
	{
		close_all(NULL, sema, 0);
		free_all(NULL, mat, sema);
		return (NULL);
	}
	philo = set_philo_philosopher(mat, sema, 0);
	if (philo == NULL || \
		refresh_time(sema, &mat->open_time, NONE) == FAIL)
	{
		close_all(philo, sema, 0);
		free_all(philo, mat, sema);
		return (NULL);
	}
	return (philo);
}

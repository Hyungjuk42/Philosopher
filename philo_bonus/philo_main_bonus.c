/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:46:01 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 21:11:48 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_philosopher(t_philo *philo, t_mat *mat)
{
	int		i;
	int		pid;
	int		stat;

	i = -1;
	while (++ i < mat->num_of_philo)
	{
		pid = fork();
		mat->pid_arr[i] = pid;
		if (pid > 0)
			continue ;
		else if (pid == 0)
			exit(philo_run(&philo[i]));
		else
		{
			while (-- i >= 0)
			{
				kill(mat->pid_arr[i], SIGTERM);
				waitpid(mat->pid_arr[i], &stat, 0);
			}
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	create_monitor(t_philo *philo, t_mat *mat)
{
	int				i;
	struct timeval	c_t;

	i = -1;
	while (++ i < mat->num_of_philo)
	{
		refresh_time(philo->sema, &philo[i].eat_time, TIME);
		if (pthread_create(&philo[i].get_time, NULL, get_time, &philo[i]) != 0)
			return (FAIL);
		if (pthread_create(&philo[i].chk_dead, NULL, chk_dead, &philo[i]) != 0)
			return (FAIL);
	}
	gettimeofday(&c_t, NULL);
	i = convert_to_ms(philo->sema, &philo->mat->open_time, &c_t);
	printf("%d: [ START    TIME ]\n", i);
	sem_post(philo->sema->open_lock);
	i = -1;
	while (++ i < mat->num_of_philo)
	{
		if (pthread_join(philo[i].chk_dead, NULL) != SUCCESS)
			return (FAIL);
		if (pthread_join(philo[i].get_time, NULL) != SUCCESS)
			return (FAIL);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	int		i;
	int		stat;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong INPUT\n");
		exit(ERROR);
	}
	philo = set_philosopher(ac, av);
	if (philo == NULL || philo->mat->repeat_num == 0)
		exit(ERROR);
	sem_wait(philo->sema->open_lock);
	if (create_philosopher(philo, philo->mat) == ERROR || \
		create_monitor(philo, philo->mat) == ERROR)
		exit(ERROR);
	i = -1;
	while (++ i < philo->mat->num_of_philo)
		kill(philo->mat->pid_arr[i], SIGTERM);
	i = -1;
	while (++ i < philo->mat->num_of_philo)
		waitpid(philo->mat->pid_arr[i], &stat, 0);
	close_all(philo, philo->sema, 0);
	set_sema_unlink(philo->mat->num_of_philo);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:56:38 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/09/06 20:59:48 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo, t_mat *mat)
{
	if (philo != NULL)
		free(philo);
	if (mat != NULL && mat->fork_mat != NULL)
		free(mat->fork_mat);
	if (mat != NULL)
		free(mat);
}

t_mat	*set_material(int ac, char **av, int num)
{
	t_mat	*mat;

	mat = (t_mat *)malloc(sizeof(t_mat));
	if (mat == NULL)
		return (NULL);
	mat->number_of_philosophers = num;
	mat->time_to_die = ft_atoi(av[2]);
	mat->time_to_eat = ft_atoi(av[3]);
	mat->time_to_sleep = ft_atoi(av[4]);
	mat->repeat_number = -1;
	mat->full_philo = 0;
	mat->is_dead = 0;
	mat->fork_mat = NULL;
	if (ac == 6)
		mat->repeat_number = ft_atoi(av[5]);
	return (mat);
}

t_philo	*set_each_philo(t_philo *philo, t_mat *mat, int num)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(mat->print_lock), NULL) != 0)
	{
		free_all(philo, mat);
		return (NULL);
	}
	while (++ i < num)
	{
		philo[i].mat = mat;
		philo[i].philo_num = i;
		philo[i].fork1 = ft_min_max(i, (i + 1) % num, 0, i);
		philo[i].fork2 = ft_min_max(i, (i + 1) % num, 1, i);
		philo[i].passed_time = 0;
		philo[i].repeat_time = 0;
		philo[i].is_full = 0;
		if (pthread_mutex_init(&mat->fork_mat[i], NULL) != 0)
		{
			free_all(philo, mat);
			return (NULL);
		}
	}
	return (philo);
}

t_mat	*chk_mat(int ac, char **av)
{
	t_mat	*mat;

	mat = set_material(ac, av, ft_atoi(av[1]));
	if (!mat)
		return (NULL);
	if (mat->number_of_philosophers < 1 || mat->time_to_die < 0 || \
	mat->time_to_eat < 0 || mat->time_to_sleep < 0 || mat->repeat_number < -1 \
	|| (mat->repeat_number == -1 && ac == 6) || mat->repeat_number == 0)
	{
		free_all(NULL, mat);
		return (NULL);
	}
	if (mat->number_of_philosophers == 1)
	{
		printf("%d 1 has taken a fork\n", 0);
		usleep(1000 * mat->time_to_die);
		printf("%d 1 is dead\n", mat->time_to_die);
		free_all(NULL, mat);
		return (NULL);
	}
	if (pthread_mutex_init(&(mat->open_restaurant), NULL) != 0)
		return (NULL);
	return (mat);
}

t_philo	*set_philosopher(int ac, char **av)
{
	t_mat	*mat;
	t_philo	*philo;

	mat = chk_mat(ac, av);
	if (mat == NULL)
		return (NULL);
	mat->fork_mat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	mat->number_of_philosophers);
	if (mat->fork_mat == NULL)
	{
		free_all(NULL, mat);
		return (NULL);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * mat->number_of_philosophers);
	if (philo == NULL)
	{
		free_all(NULL, mat);
		return (NULL);
	}
	set_each_philo(philo, mat, mat->number_of_philosophers);
	return (philo);
}

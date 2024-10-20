/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 01:03:28 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 16:39:43 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_atoi libft 걸로 바꾸기
// libft 사용 금지
// exit 함수 지우기
/**
 * ms X has taken a fork
 * ms X is eating
 * ms X is sleeping
 * ms X is thinking
 * ms X died
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define INT_MIN -2147483648
# define MAX 1000000000
# define DIE 1
# define ERROR 0

typedef struct s_material
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				repeat_number;
	int				full_philo;
	int				is_dead;
	struct timeval	open_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	full_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	open_restaurant;
	pthread_mutex_t	*fork_mat;
}	t_mat;

typedef struct s_philo
{
	int				philo_num;
	int				fork1;
	int				fork2;
	int				passed_time;
	int				repeat_time;
	int				is_full;
	pthread_t		thread;
	struct timeval	cur_time;
	struct timeval	fork_time;
	struct timeval	think_time;
	t_mat			*mat;
}	t_philo;

// philo_utils
void	free_all(t_philo *philo, t_mat *mat);
int		ft_min_max(int a, int b, int flag, int philo_num);
void	get_sleep(t_mat *mat, struct timeval *s, int time);
t_philo	*set_philosopher(int ac, char **av);
int		printf_m(char *s, t_philo *philo, t_mat *mat);
int		philosopher_fork_lock(t_philo *philo, t_mat *mat);
int		philosopher_fork_unlock(t_philo *philo, t_mat *mat);
int		convert_to_ms(struct timeval *s, struct timeval *e);
void	make_dead(t_mat *mat);
int		is_dead_mutex(t_mat *mat, int flag);
int		full_mutex(t_mat *mat, int flag);
void	increase_full(t_mat *mat);
int		time_mutex(t_philo *philo, t_mat *mat, struct timeval *cur_t);
void	refresh_time(t_philo *philo, t_mat *mat);
void	make_full(t_philo *philo);
int		is_full_mutex(t_philo *philo, int flag);

void	monitoring_philosopher(t_philo *philo, t_mat *mat);
void	*philo_run(void *p_info);
int		ft_atoi(const char *str);
#endif
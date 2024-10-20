/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:34:51 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 20:19:00 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# define INT_MIN -2147483648
# define MAX 1000000000
# define SUCCESS 0
# define ERROR 1
# define FAIL 1
# define LIVE 0
# define DIE 1
# define FULL 2
# define NONE 2
# define OPEN 3
# define TIME 4

typedef struct s_mat
{
	struct timeval	open_time;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				repeat_num;
	int				is_dead;
	pid_t			*pid_arr;
}	t_mat;

typedef struct s_sema
{
	sem_t			*chk_is_dead;
	sem_t			*fork_con;
	sem_t			*fork;
	sem_t			*time_lock;
	sem_t			*print_lock;
	sem_t			*dead_lock;
	sem_t			*open_lock;
}	t_sema;

typedef struct s_philo
{
	t_mat			*mat;
	t_sema			*sema;
	struct s_philo	*first_philo;
	pthread_t		get_time;
	pthread_t		chk_dead;
	struct timeval	eat_time;
	sem_t			*loop_lock;
	int				repeat_time;
	int				philo_num;
	int				state;
	int				passed_time;
}	t_philo;

// set
t_philo	*set_philosopher(int ac, char **av);

// thread
void	*chk_dead(void *arg);
void	*get_time(void *arg);

// utils
int		convert_to_ms(t_sema *sema, struct timeval *s, struct timeval *e);
void	set_sema_unlink(int num_of_philo);
int		refresh_time(t_sema *sema, struct timeval *t_val, int flag);
void	free_all(t_philo *philo, t_mat *mat, t_sema *sema);
void	close_all(t_philo *philo, t_sema *sema, int i);

int		get_sleep(t_philo *philo, struct timeval *s, int time);
int		philosopher_fork_lock(t_philo *philo, t_sema *sema);
int		philosopher_fork_unlock(t_sema *sema);
int		printf_m(char *s, t_philo *philo);
int		philo_run(t_philo *philo);

// libft
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);

// monitor
int		is_dead_mutex(t_philo *philo);
void	make_dead(t_philo *philo, int flag);
t_mat	*only_one(t_mat *mat);

#endif
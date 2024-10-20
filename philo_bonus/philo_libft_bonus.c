/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_libft_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjuk <hyungjuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:56:27 by hyungjuk          #+#    #+#             */
/*   Updated: 2023/08/30 17:26:02 by hyungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static unsigned int	intlen(int n, int *idx)
{
	unsigned int	un;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		*idx += 1;
	}
	else if (n == 0)
	{
		*idx = 1;
		return (0);
	}
	un = n * sign;
	n = un / 10;
	*idx += 1;
	while (n)
	{
		n /= 10;
		*idx += 1;
	}
	return (un);
}

char	*ft_itoa(int n)
{
	char			*arr;
	unsigned int	un;
	int				idx;

	idx = 0;
	un = intlen(n, &idx);
	arr = malloc (sizeof(char) * (idx + 1));
	if (!arr)
		return (0);
	if (n < 0)
		arr[0] = '-';
	else if (n == 0)
		arr[0] = '0';
	arr[idx] = '\0';
	while (un)
	{
		idx --;
		arr[idx] = un % 10 + '0';
		un /= 10;
	}
	return (arr);
}

int	ft_atoi(const char *str)
{
	long long	num;
	long long	sign;
	int			idx;

	num = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str ++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str ++;
	while ('0' == *str)
		str ++;
	idx = 0;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		num *= 10;
		num += str[idx] - '0';
		idx ++;
	}
	num *= sign;
	if (idx > 11 || num < INT_MIN || num > MAX || str[idx] != 0)
		return (-10);
	return ((int)num);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	int		idx1;
	int		idx2;

	idx1 = 0;
	idx2 = 0;
	while (s1[idx1])
		idx1 ++;
	while (s2[idx2])
	{
		idx1 ++;
		idx2 ++;
	}
	s_join = malloc(sizeof(char) * (idx1 + 1));
	if (!s_join)
		return (0);
	idx1 = -1;
	idx2 = -1;
	while (s1[++ idx1])
		s_join[idx1] = s1[idx1];
	while (s2[++ idx2])
		s_join[idx1 ++] = s2[idx2];
	s_join[idx1] = '\0';
	return (s_join);
}

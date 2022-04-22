/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:36:24 by jhii              #+#    #+#             */
/*   Updated: 2022/04/22 14:11:13 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	long	result;
	long	negative;

	result = 0;
	negative = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
		if (result * negative > 2147483647)
			return (-1);
		if (result * negative < -2147483648)
			return (0);
	}
	return (result * negative);
}

void	mulwaitpid(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->n_philo)
		waitpid(table->group[i++].pid, &status, 0);
}

long long	get_time(void)
{
	struct timeval	timer;
	long long		result;

	gettimeofday(&timer, NULL);
	result = (long long)timer.tv_sec * 1000000;
	result = result + (long long)timer.tv_usec;
	result = result / 1000;
	return (result);
}

void	ft_msleep(int time, long long start)
{
	long long	cur;

	cur = 0;
	while (cur < (long long)time)
	{
		cur = get_time() - start;
		usleep(100);
	}
}

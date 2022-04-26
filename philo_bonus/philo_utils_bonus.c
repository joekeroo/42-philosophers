/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:08:13 by jhii              #+#    #+#             */
/*   Updated: 2022/04/26 16:43:53 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	table_init(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_count = -1;
	if (argc == 6)
		table->philo_eat_count = ft_atoi(argv[5]);
	table->eat_count = 0;
	table->stop = 0;
	table->p_death = 0;
	table->pid = malloc(sizeof(pid_t *) * table->n_philo);
	sem_unlink("/print_mutex");
	sem_unlink("/fork_mutex");
	table->print_mutex = sem_open("/print_mutex", O_CREAT, 0644, 1);
	table->fork_mutex = sem_open("/fork_mutex", O_CREAT, 0644,
			table->n_philo);
}

void	print_msg(t_table *table, char *str)
{
	sem_wait(table->print_mutex);
	if (table->stop == 0)
	{
		if (ft_strncmp(str, "died", 4) == 0)
			printf(RED "%lld %d %s\n", get_time(), table->index, str);
		if (ft_strncmp(str, "is thinking", 11) == 0)
			printf(MAG "%lld %d %s\n", get_time(), table->index, str);
		if (ft_strncmp(str, "is sleeping", 11) == 0)
			printf(YEL "%lld %d %s\n", get_time(), table->index, str);
		if (ft_strncmp(str, "has taken a fork", 16) == 0)
			printf(CYN "%lld %d %s\n", get_time(), table->index, str);
		if (ft_strncmp(str, "is eating", 9) == 0)
			printf(GRN "%lld %d %s\n", get_time(), table->index, str);
	}
	sem_post(table->print_mutex);
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

void	ft_msleep(long long time, t_table *table)
{
	long long	start;

	start = get_time();
	while (table->stop == 0)
	{
		if (get_time() - start >= time)
			break ;
		usleep(100);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:08:13 by jhii              #+#    #+#             */
/*   Updated: 2022/04/19 17:43:55 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int argc, char **argv)
{
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_count = 0;
	if (argc == 6)
		table->philo_eat_count = ft_atoi(argv[5]);
	table->curr_philo = 0;
	table->curr_death = 0;
	table->group = malloc(sizeof(t_philo) * table->n_philo);
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

void	philo_think(t_table *table, int philo)
{
	table->group[philo].start_time = get_time();
	table->group[philo].death_time = table->group[philo].start_time
		+ table->time_to_die;
	table->timestamp = get_time();
	printf(MAG "%lld Philosopher %d is thinking\n",
		table->timestamp, philo);
}

void	philo_sleep(t_table *table, int philo)
{
	table->timestamp = get_time();
	printf(YEL "%lld Philosopher %d is sleeping\n",
		table->timestamp, philo);
	msleep(table->time_to_sleep);
}

void	philo_eat(t_table *table, int philo)
{
	table->timestamp = get_time();
	printf(CYN "%lld Philosopher %d has taken a fork\n",
		table->timestamp, philo);
	table->timestamp = get_time();
	printf(CYN "%lld Philosopher %d has taken a fork\n",
		table->timestamp, philo);
	table->group[philo].start_time = get_time();
	table->group[philo].death_time = table->group[philo].start_time
		+ table->time_to_die;
	table->timestamp = get_time();
	printf(GRN "%lld Philosopher %d is eating\n",
		table->timestamp, philo);
	msleep(table->time_to_eat);
}

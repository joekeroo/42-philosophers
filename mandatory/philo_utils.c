/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:08:13 by jhii              #+#    #+#             */
/*   Updated: 2022/04/21 15:00:19 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int argc, char **argv)
{
	int	i;

	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_count = 99999999;
	if (argc == 6)
		table->philo_eat_count = ft_atoi(argv[5]);
	table->curr_philo = 0;
	table->start_routine = 0;
	table->start_death = 0;
	table->done_eating = 0;
	table->group = malloc(sizeof(t_philo) * table->n_philo);
	i = 0;
	while (i < table->n_philo)
		table->group[i++].eat_count = 0;
	i = 0;
	while (i < table->n_philo)
		table->group[i++].death_time = get_time() + 100000;
}

void	philo_think(t_table *table, int philo)
{
	printf(MAG "%lld %d is thinking\n", get_time(), philo);
	table->group[philo].death_time = get_time()
		+ (long long)table->time_to_die;
}

void	philo_live(t_table *table, int philo)
{
	pthread_mutex_lock(&table->group[philo].fork);
	pthread_mutex_lock(&table->group[(philo + 1) % table->n_philo].fork);
	philo_eat(table, philo);
	pthread_mutex_unlock(&table->group[philo].fork);
	pthread_mutex_unlock(&table->group[(philo + 1) % table->n_philo].fork);
	philo_sleep(table, philo);
}

void	philo_sleep(t_table *table, int philo)
{
	if (table->p_death == 0)
		printf(YEL "%lld %d is sleeping\n", get_time(), philo);
	if (table->group[philo].eat_count == table->philo_eat_count)
		table->done_eating++;
	ft_msleep(table->time_to_sleep, get_time());
}

void	philo_eat(t_table *table, int philo)
{
	if (table->p_death == 0)
	{
		printf(CYN "%lld %d has taken a fork\n", get_time(), philo);
		printf(CYN "%lld %d has taken a fork\n", get_time(), philo);
		printf(GRN "%lld %d is eating\n", get_time(), philo);
	}
	table->group[philo].eat_count++;
	table->group[philo].death_time = get_time()
		+ (long long)table->time_to_die;
	ft_msleep(table->time_to_eat, get_time());
}

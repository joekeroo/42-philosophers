/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:56 by jhii              #+#    #+#             */
/*   Updated: 2022/04/21 15:10:48 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*check_death(void *oldtable)
{
	t_table		*table;
	int			philo;
	long long	timestamp;

	philo = 0;
	table = oldtable;
	while (table->start_death == 0)
		usleep(table->n_philo);
	while (philo < table->n_philo && table->p_death == 0)
	{
		timestamp = get_time();
		if (table->done_eating == table->n_philo)
			table->p_death = 1;
		if (timestamp > table->group[philo].death_time && table->p_death == 0)
		{
			printf(RED "%lld %d died\n", timestamp, philo);
			table->p_death = 1;
		}
		if (philo == table->n_philo - 1)
			philo = 0;
		else
			philo++;
	}
	return (0);
}

static	void	*routine(void *oldtable)
{
	int		i;
	int		philo;
	t_table	*table;

	table = oldtable;
	pthread_mutex_lock(&table->mutex);
	philo = table->curr_philo++;
	pthread_mutex_unlock(&table->mutex);
	while (table->start_routine == 0)
		usleep(table->n_philo);
	philo_think(table, philo);
	if (philo % 2 == 0)
		usleep(table->time_to_eat * 500);
	table->start_death = 1;
	i = 0;
	while (i < table->philo_eat_count && table->p_death == 0)
	{
		philo_live(table, philo);
		i++;
	}
	return (0);
}

void	philo(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->mutex, NULL);
	while (i < table->n_philo)
		pthread_mutex_init(&table->group[i++].fork, NULL);
	i = 0;
	while (i < table->n_philo)
		pthread_create(&table->group[i++].philo, NULL, *routine, table);
	table->start_routine = 1;
	pthread_create(&table->death, NULL, *check_death, table);
	pthread_join(table->death, NULL);
	i = 0;
	while (i < table->n_philo)
		pthread_join(table->group[i++].philo, NULL);
	return ;
}

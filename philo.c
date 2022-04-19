/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:56 by jhii              #+#    #+#             */
/*   Updated: 2022/04/19 16:59:31 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	*check_death(void *oldtable)
{
	int		philo;
	t_table	*table;

	table = oldtable;
	pthread_mutex_lock(&table->mutex);
	philo = table->curr_death++;
	pthread_mutex_unlock(&table->mutex);
	while (get_time() < table->group[philo].death_time)
		;
	table->timestamp = get_time();
	printf(RED "%lld Philosopher %d died\n",
		table->timestamp, philo);
	exit(0);
	return (0);
}

static	void	*routine(void *oldtable)
{
	int		philo;
	t_table	*table;

	table = oldtable;
	pthread_mutex_lock(&table->mutex);
	philo = table->curr_philo++;
	pthread_mutex_unlock(&table->mutex);
	philo_think(table, philo);
	pthread_mutex_lock(&table->group[philo].fork);
	pthread_mutex_lock(&table->group[(philo + 1) % table->n_philo].fork);
	philo_eat(table, philo);
	pthread_mutex_unlock(&table->group[philo].fork);
	pthread_mutex_unlock(&table->group[(philo + 1) % table->n_philo].fork);
	philo_sleep(table, philo);
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
	pthread_create(&table->death, NULL, *check_death, table);
	i = 0;
	while (i < table->n_philo)
		pthread_join(table->group[i++].philo, NULL);
	pthread_join(table->death, NULL);
	return ;
}

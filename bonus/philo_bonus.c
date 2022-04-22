/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:56 by jhii              #+#    #+#             */
/*   Updated: 2022/04/22 16:31:10 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*check_death(void *oldtable)
{
	t_table		*table;
	long long	timestamp;

	table = oldtable;
	while (1)
	{
		timestamp = get_time();
		if (table->done_eating >= 1)
			exit(0);
		if (timestamp > table->group[table->philo].death_time)
		{
			printf(RED "%lld %d died\n", timestamp, table->philo);
			exit(0);
		}
	}
	return (0);
}

static	void	routine(t_table *table, int philo)
{
	int	i;

	i = 0;
	philo_think(table, philo);
	pthread_create(&table->death, NULL, *check_death, table);
	while (i < table->philo_eat_count)
	{
		sem_wait(&table->group[philo].mutex);
		philo_eat(table, philo);
		sem_post(&table->group[(philo + 1) % table->n_philo].mutex);
		philo_sleep(table, philo);
		i++;
	}
	pthread_join(table->death, NULL);
	exit(0);
}

static	void	fork_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo = i;
		table->group[i].pid = fork();
		if (table->group[i].pid == 0)
			return (routine(table, i));
		i++;
	}
	mulwaitpid(table);
	exit(0);
}

void	philo(t_table *table, int argc, char **argv)
{
	table_init(table, argc, argv);
	fork_philos(table);
	return ;
}

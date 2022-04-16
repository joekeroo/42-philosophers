/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:56 by jhii              #+#    #+#             */
/*   Updated: 2022/04/16 19:03:00 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	*routine(void *oldtable)
{
	t_table	*table;

	table = oldtable;
	pthread_mutex_lock(&table->mutex);
	printf("before sleep\n");
	sleep(1);
	printf("after sleep\n");
	pthread_mutex_unlock(&table->mutex);
	return (0);
}

void	philo(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->mutex, NULL);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	while (i < table->number_of_philo)
		pthread_create(&table->philos[i++].person, NULL, &routine, &table);
	i = 0;
	while (i < table->number_of_philo)
		pthread_join(table->philos[i++].person, NULL);
	return ;
}

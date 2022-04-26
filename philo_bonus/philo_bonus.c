/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:38:56 by jhii              #+#    #+#             */
/*   Updated: 2022/04/26 17:01:58 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	*check_death(void *oldtable)
{
	t_table		*table;

	table = oldtable;
	while (table->stop == 0)
	{
		usleep(100);
		if (get_time() - table->life > table->time_to_die)
		{
			table->p_death = 1;
			sem_wait(table->print_mutex);
			printf(RED "%lld %d died\n", get_time(), table->index);
			table->stop = 1;
			break ;
		}
		if (table->philo_eat_count != -1
			&& table->eat_count >= table->philo_eat_count)
		{
			table->stop = 1;
			break ;
		}
	}
	if (table->p_death)
		exit(1);
	exit(0);
}

static	void	routine(t_table *table)
{
	pthread_create(&table->death, NULL, &check_death, table);
	if (table->index % 2 == 1)
		usleep(1000);
	while (1)
	{
		print_msg(table, "is thinking");
		sem_wait(table->fork_mutex);
		print_msg(table, "has taken a fork");
		sem_wait(table->fork_mutex);
		print_msg(table, "has taken a fork");
		print_msg(table, "is eating");
		table->life = get_time();
		ft_msleep(table->time_to_eat, table);
		sem_post(table->fork_mutex);
		sem_post(table->fork_mutex);
		table->eat_count += 1;
		print_msg(table, "is sleeping");
		ft_msleep(table->time_to_sleep, table);
	}
	pthread_join(table->death, NULL);
}

static	void	end_routine(t_table *table)
{
	int		i;
	int		status;

	i = 0;
	while (i < table->n_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < table->n_philo)
				kill(table->pid[i++], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(table->print_mutex);
	sem_close(table->fork_mutex);
	sem_unlink("/print_mutex");
	sem_unlink("/fork_mutex");
}

void	philo_bonus(t_table *table, int argc, char **argv)
{
	int	i;

	i = 0;
	table_init(table, argc, argv);
	while (i < table->n_philo)
	{
		table->pid[i] = fork();
		if (table->pid[i] == 0)
		{
			table->index = i + 1;
			table->life = get_time();
			routine(table);
		}
		i++;
	}
	end_routine(table);
	return ;
}

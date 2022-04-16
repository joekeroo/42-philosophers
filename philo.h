/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:29:18 by jhii              #+#    #+#             */
/*   Updated: 2022/04/16 19:01:39 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	person;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	pthread_mutex_t	mutex;
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		philo_eat_count;
}	t_table;

void	philo(t_table *table);
void	philo_init(t_table *table, int argc, char **argv);
int		ft_atoi(const char *str);
void	free_malloc(char **tab);

#endif

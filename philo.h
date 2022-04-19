/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:29:18 by jhii              #+#    #+#             */
/*   Updated: 2022/04/19 17:40:37 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RESET	"\x1B[0m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	long long		start_time;
	long long		death_time;
}	t_philo;

typedef struct s_table
{
	t_philo			*group;
	pthread_t		death;
	pthread_mutex_t	mutex;
	int				curr_philo;
	int				curr_death;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_count;
	long long		timestamp;
}	t_table;

void		philo(t_table *table);
void		table_init(t_table *table, int argc, char **argv);
void		philo_eat(t_table *table, int philo);
void		philo_sleep(t_table *table, int philo);
void		philo_think(t_table *table, int philo);
void		free_malloc(t_table *table);
void		msleep(int time);
int			ft_atoi(const char *str);
long long	get_time(void);

#endif

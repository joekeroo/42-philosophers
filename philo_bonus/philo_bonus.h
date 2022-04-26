/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:29:18 by jhii              #+#    #+#             */
/*   Updated: 2022/04/26 16:45:06 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_table
{
	pthread_t	death;
	sem_t		*fork_mutex;
	sem_t		*print_mutex;
	pid_t		*pid;
	int			stop;
	int			index;
	long long	life;
	int			p_death;
	int			eat_count;
	int			n_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			philo_eat_count;
}	t_table;

int			check_input(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
long long	get_time(void);
void		print_msg(t_table *table, char *str);
void		ft_msleep(long long time, t_table *table);
void		table_init(t_table *table, int argc, char **argv);
void		philo_bonus(t_table *table, int argc, char **argv);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:27:03 by jhii              #+#    #+#             */
/*   Updated: 2022/04/26 14:04:44 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (check_input(argc, argv) < 0)
	{
		printf("Error\n");
		return (0);
	}
	philo_bonus(&table, argc, argv);
	return (0);
}

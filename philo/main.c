/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:27:03 by jhii              #+#    #+#             */
/*   Updated: 2022/04/21 18:14:24 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	table_init(&table, argc, argv);
	philo(&table);
	free(table.group);
	return (0);
}

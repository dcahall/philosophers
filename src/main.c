/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:28:36 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/17 13:14:51 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int	*value;
	// int i = 0;
	// t_philo *philo;

	if (argc != 5 && argc != 6)
		return (ERROR);
	value = parse_arg(argc, argv);
	if (!value)
		return (ERROR);
	if (ft_init(value, argc) == ERROR)
		return (ERROR);
	return (SUCCESS);
	// while (i < value[0])
	// {
	// 	printf("id philo: %d\t current time: %ld\n", philo[i].num_philo, philo[i].time);
	// 	i++;
	// }
	// for (i = 0; i < argc - 1; i++)
		// printf("%d\n", value[i]);
}
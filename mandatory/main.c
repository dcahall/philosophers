/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:28:36 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/28 12:14:04 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int	*value;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	value = parse_arg(argc, argv);
	if (!value)
		return (EXIT_FAILURE);
	if (ft_init(value, argc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

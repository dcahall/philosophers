/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:00:19 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/19 16:55:45 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_symbol(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 1;
	while (i < (size_t)argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (ERROR);
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

static int	*convers_argc_to_int(int argc, char **argv)
{
	size_t	i;
	int		*value;

	i = 0;
	value = malloc(sizeof(int) * argc - 1);
	if (!value)
		return (NULL);
	while (argv[i + 1])
	{
		value[i] = ft_atoi(argv[i + 1]);
		if (value[i] < 0)
		{
			free(value);
			return (NULL);
		}
		i++;
	}
	return (value);
}

int	*parse_arg(int argc, char **argv)
{
	if (check_symbol(argc, argv) == ERROR)
		return (NULL);
	else
		return (convers_argc_to_int(argc, argv));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:00:19 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/27 19:09:02 by dcahall          ###   ########.fr       */
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
				return (EXIT_FAILURE);
			j++;
		}
		j = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	*convers_argc_to_int(int argc, char **argv)
{
	int		i;
	int		*value;

	i = 0;
	value = malloc(sizeof(int) * argc);
	if (!value)
	{
		error_message("Error malloc (conver_argc_to_int)");
		return (NULL);
	}
	while (i < argc - 1)
	{
		value[i] = ft_atoi(argv[i + 1]);
		if (value[i] == 0)
		{
			error_message("Error arg");
			free(value);
			return (NULL);
		}
		i++;
	}
	return (value);
}

int	*parse_arg(int argc, char **argv)
{
	if (check_symbol(argc, argv) == EXIT_FAILURE)
		return (NULL);
	else
		return (convers_argc_to_int(argc, argv));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:00:19 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 16:28:39 by dcahall          ###   ########.fr       */
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
				return (error_message("Error ft_isdigit"));
			j++;
		}
		j = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
** We always allocate memory for 6 cells, even if there are 5 
** arguments. In cell 6 we note how many philosophers have already eaten. 
** If there are 4 arguments, then cell 5 remains unused
*/

static int	*convers_argc_to_int(int argc, char **argv)
{
	int		i;
	int		*value;

	i = 0;
	value = malloc(sizeof(int) * ARG6);
	if (!value)
	{
		error_message("Error malloc (conver_argc_to_int)");
		return (NULL);
	}
	if (argc == ARG6)
		value[ARG6 - 1] = 0;
	while (i < argc - 1)
	{
		value[i] = ft_atoi(argv[i + 1]);
		if (value[i] <= 0)
		{
			error_message("Error arg");
			free(value);
			return (NULL);
		}
		i++;
	}
	return (value);
}

/*
** Checks characters for validity.
** Allocates memory for parameters and writes them
*/

int	*parse_arg(int argc, char **argv)
{
	if (check_symbol(argc, argv) == EXIT_FAILURE)
		return (NULL);
	else
		return (convers_argc_to_int(argc, argv));
}

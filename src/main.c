/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:28:36 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/12 18:28:38 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int *ft_free(int *value)
{
	if (value)
		free(value);
	return (NULL);
}

static int	check_symbol(int argc, char **argv)
{
	int	i;
	int j;

	j = 0;
	i = 1;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	*convers_argc_to_int(int argc, char **argv)
{
	int	i;
	int j;
	int	*value;

	i = 1;
	j = 0;
	value = malloc(sizeof(int) * argc - 1);
	if (!value)
		return (NULL);
	while (argv[i])
	{
		value[j] = ft_atoi(argv[i]);
		if (ft_strlen(argv[i]) > LEN_INT)
			return (ft_free(value));
		if (value[j] < 0)
			return (ft_free(value));
		j++;
		i++;
	}
	return (value);
}

static int	*parse_arg(int argc, char **argv)
{
	if (!check_symbol(argc, argv))
		return (NULL);
	else
		return (convers_argc_to_int(argc, argv));
}

int	main(int argc, char **argv)
{
	int	*value;

	if (argc != 5 && argc != 6)
		return (1);
	value = parse_arg(argc, argv);
	if (!value)
		return (1);
	while (value)
	{
		printf("%d\n", *value);
		value++;
	}

}


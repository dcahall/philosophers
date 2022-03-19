/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/19 20:26:37 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_ph(int *value, int argc, t_common *common)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philo) * value[0]);
	if (!philo)
		return (NULL);
	while (i < value[0])
	{
		philo[i].num_philo = i + 1;
		philo[i].common = common;
		philo[i].meal_numbers = 0;
		if (argc == ARG6)
			philo[i].arg6 = EXIST;
		else
			philo[i].arg6 = NOT_EXIST;
		i++;
	}
	return (philo);
}

static void	set_forks(t_philo *philo, pthread_mutex_t *forks, int value)
{
	(philo + value)->right_fork = &forks[value];
	(philo + value)->left_fork = &forks[0];
	while (value > 0)
	{
		value--;
		philo[value].right_fork = &forks[value];
		philo[value].left_fork = &forks[value + 1];
	}
}

static int	init_mutex(t_common *common)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(common->access_print, NULL))
		return (ERROR);
	while (i < common->value[0])
	{
		if (pthread_mutex_init((common->all_forks + i), NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static t_common	*init_common_data(int *value)
{
	t_common		*common;

	common = malloc (sizeof(t_common));
	if (!common)
		return (NULL);
	common->value = value;
	common->access_print = NULL;
	common->all_forks = NULL;
	common->all_tid = NULL;
	common->all_forks = malloc (sizeof(pthread_mutex_t) * value[0]);
	common->access_print = malloc (sizeof(pthread_mutex_t));
	common->all_tid = malloc(sizeof(pthread_t) * value[0]);
	if (!common->all_forks || !common->access_print || !common->all_tid)
	{
		ft_free(NULL, common);
		return (NULL);
	}
	return (common);
}

int	ft_init(int *value, int argc)
{
	t_philo			*philo;
	t_common		*common;

	common = init_common_data(value);
	if (!common)
		return (ERROR);
	philo = init_ph(value, argc, common);
	if (!philo)
		return (ft_free(NULL, common));
	if (init_mutex(common) ==  ERROR)
	{
		ft_free(philo, common);
		return (ERROR);
	}
	set_forks(philo, common->all_forks, value[0] - 1);
	if (start_philo(philo) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/21 20:20:19 by dcahall          ###   ########.fr       */
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
		philo[i].time_start = get_time();
		philo[i].last_meal = philo[i].time_start;
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
	while (value)
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
	while (i < common->value[0])
	{
		if (pthread_mutex_init((common->all_forks + i), NULL))
			return (error_message("Error pthread_mutex_init (init_mutex)"));
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
	common->all_forks = NULL;
	common->all_tid = NULL;
	common->all_alive = YES;
	common->all_forks = malloc (sizeof(pthread_mutex_t) * value[0]);
	common->all_tid = malloc(sizeof(pthread_t) * value[0]);
	if (!common->all_forks || !common->all_tid)
	{
		error_message("Error malloc (init_common_data)");
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
	{
		ft_free(NULL, common);
		return (ERROR);
	}
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

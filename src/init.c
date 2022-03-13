/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/13 15:21:54 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philo(int *value, int argc)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * value[0]);
	if (!philo)
		return (NULL);
	while (i < value[0])
	{
		philo[i].num_philo = i + 1;
		philo[i].value = value;
		philo[i].time = get_time();
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
	(philo + value)->rightFork = &forks[value];
	(philo + value)->leftFork = &forks[0];
	while (--value)
	{
		philo[value].rightFork = &forks[value];
		philo[value].leftFork = &forks[value + 1];
	}
}

t_philo *ft_init(int *value, int argc)
{
	t_philo 		*philo;
	pthread_mutex_t *forks;

	forks = malloc (sizeof(pthread_mutex_t) * value[0]);
	if (!forks)
		return (NULL);
	philo = init_philo(value, argc);
	if (!philo)
		return (NULL);
	set_forks(philo, forks, value[0] - 1);
	return (philo);
}
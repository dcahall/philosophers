/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/16 20:45:37 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_philo(int *value, int argc, pthread_mutex_t *access_forks)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philo) * value[0]);
	if (!philo)
		return (NULL);
	if (pthread_mutex_init(access_forks, NULL))
		return (NULL);
	while (i < value[0])
	{
		philo[i].num_philo = i + 1;
		philo[i].value = value;
		philo[i].time = get_time();
		philo[i].accessForks = access_forks;
		if (argc == ARG6)
			philo[i].arg6 = EXIST;
		else
			philo[i].arg6 = NOT_EXIST;
		i++;
	}
	return (philo);
}

static int	set_forks(t_philo *philo, pthread_mutex_t *forks, int value)
{
	(philo + value)->rightFork = &forks[value];
	(philo + value)->leftFork = &forks[0];
	if (pthread_mutex_init(philo[value].rightFork))
		return (ERROR);
	while (--value)
	{
		if (pthread_mutex_init(philo[value].rightFork))
			return (ERROR);
		philo[value].rightFork = &forks[value];
		philo[value].leftFork = &forks[value + 1];
	}
}

int	ft_init(int *value, int argc)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*access_forks;
	pthread_t		*tid;

	forks = malloc (sizeof(pthread_mutex_t) * value[0]);
	if (!forks)
		return (ft_free(NULL, forks, value, NULL));
	access_forks = malloc(sizeof(pthread_mutex_t));
	if (!access_forks)
		return (ERROR);
	philo = init_philo(value, argc, access_forks);
	if (!philo)
		return (ft_free(philo, forks, value, NULL));
	if (set_forks(philo, forks, value[0] - 1) = ERROR)
		return (ERROR);	
	tid = malloc(sizeof(pthread_t) * value[0]);
	if (!tid)
		return (ft_free(philo, forks, value, tid));
	if (start_philo(philo, value, tid) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

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

void *run_philo(void *ph)
{
	t_philo	*philo;
	// int 	i;

	// i = 0;
	philo = (t_philo *)ph;

	// while (i < philo->value[0])
	// {
		printf("I'm a procces number %d\n", philo->num_philo);
	// 	i++;
	// }
	return (NULL);
}

static void *start_philo(t_philo *philo, int *value, pthread_t *tid)
{
	int	i;

	i = 0;
	while (i < value[0])
	{
		pthread_create(&tid[i], NULL, run_philo, (void *)(philo + i));
		i++;
	}
	i = 0;
	while (i < value[0])
	{
		pthread_join(tid[i], NULL);
		i++;
	}
	return (NULL);
}

int *ft_init(int *value, int argc)
{
	t_philo 		*philo;
	pthread_mutex_t *forks;
	pthread_t		*tid;

	forks = malloc (sizeof(pthread_mutex_t) * value[0]);
	if (!forks)
		return (ft_free(NULL, forks, value, NULL));
	philo = init_philo(value, argc);
	if (!philo)
		return (ft_free(philo, forks, value, NULL));
	set_forks(philo, forks, value[0] - 1);
	tid = malloc(sizeof(pthread_t) * value[0]);
	if (!tid)
		return (ft_free(philo, forks, value, tid));
	if (!start_philo(philo, value, tid))
		return (ft_free(philo, forks, value, tid));
	return (NULL);
}
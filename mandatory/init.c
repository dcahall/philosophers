/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/31 12:40:14 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*init_ph(int *value, int argc, pthread_mutex_t *print)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *) malloc(sizeof(t_philo) * value[0]);
	if (!philo)
		return (NULL);
	while (i < value[0])
	{
		philo[i].print = print;
		philo[i].value = value;
		philo[i].num_philo = i + 1;
		philo[i].time_start = get_time();
		philo[i].last_meal = philo[i].time_start;
		if (argc == ARG6)
			philo[i].meal_numbers = value[4];
		else
			philo[i].meal_numbers = NOT_EXIST;
		i++;
	}
	return (philo);
}

static int	set_forks(t_philo *philo, int value)
{
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (value + 1));
	if (!forks)
		return (EXIT_FAILURE);
	(philo + value)->right_fork = &forks[value];
	(philo + value)->left_fork = &forks[0];
	if (pthread_mutex_init((forks + value), NULL))
		return (error_message("Error pthread_mutex_init"));
	if (pthread_mutex_init((philo->print), NULL))
		return (error_message("Error pthread_mutex_init"));
	while (value)
	{
		value--;
		philo[value].right_fork = &forks[value];
		philo[value].left_fork = &forks[value + 1];
		if (pthread_mutex_init((forks + value), NULL))
			return (error_message("Error pthread_mutex_init"));
	}
	return (EXIT_SUCCESS);
}

static int	create_threads(t_philo *philo, pthread_t *tid, int *value)
{
	int	i;

	i = 0;
	while (i < value[0])
	{
		if (pthread_create(&tid[i], NULL, run_philo, (void *)(&philo[i])) != 0)
			return (error_message("Error pthread_create"));
		i += 2;
		if (i >= value[0] && i % 2 == 0)
			i = 1;
	}
	if (pthread_create((tid + value[0]), NULL, ft_undertaker, (void *)philo))
		return (error_message("Error pthread_create"));
	i = 0;
	while (i <= value[0])
	{
		if (pthread_join(tid[i], NULL))
			return (error_message("Error pthread_join"));
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	start_philo(t_philo *philo, int *value)
{
	pthread_t	*tid;

	tid = (pthread_t *) malloc(sizeof(pthread_t) * (value[0] + 1));
	if (!tid)
		return (ft_free(value, philo, NULL, philo->print));
	if (create_threads(philo, tid, value) == EXIT_FAILURE)
		return (ft_free(value, philo, tid, philo->print));
	if (mutex_destroy(philo) == EXIT_FAILURE)
		return (ft_free(value, philo, tid, philo->print));
	ft_free(value, philo, tid, philo->print);
	return (EXIT_SUCCESS);
}

int	ft_init(int *value, int argc)
{
	t_philo			*philo;
	pthread_mutex_t	*print;

	print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!print)
		return (ft_free(value, NULL, NULL, NULL));
	philo = init_ph(value, argc, print);
	if (!philo)
		return (ft_free(value, NULL, NULL, print));
	if (set_forks(philo, value[0] - 1) == EXIT_FAILURE)
		return (ft_free(value, philo, NULL, print));
	if (start_philo(philo, value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

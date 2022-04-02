/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 16:02:02 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** We allocate memory for philosophers (structures), the 
** number of structures is equal to the number of 
** philosophers, initialize the fields of the structure.
** By the variable meals_numbers, we track whether 
** philosophers need to eat a certain number of times, if so, 
** the value of how many times they need to eat is stored there.
*/

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

/*
** We allocate memory for forks, we distribute forks to 
** philosophers. Each philosopher has 2 forks, the right 
** fork belongs to the current philosopher, and the left fork 
** belongs to the neighbor. Initializing mutexes
*/

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

/*
** Creates streams of even philosophers first, then odd 
** ones, also creates an undertaker stream that tracks the 
** death of philosophers and the number of dinners. We 
** are waiting for all the philosopher and undertaker using 
** the pthread_join function
*/

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

/*
** Allocates memory for thread identifiers (we create 1 more, one
** thread will monitor whether any of the philosophers have died). 
** We are sending philosophers to launch. When the philosophers 
** have worked out, we destroy mutexes (only an open mutex can 
** be destroyed) and clear the memory
*/

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

/*
** Initializes the mutex, creates the structure, initializes the structure
*/

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

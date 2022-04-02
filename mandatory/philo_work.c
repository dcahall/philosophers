/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/04/02 16:16:04 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Destroys all mutexes, mutexes must be in the open 
** state, since the value of the stop_run flag blocks only 
** printing, all fork mutexes are in the open state, and the 
** print mutex needs to be opened. Mutexes can, but it is not 
** desirable to close them in different threads, but they cannot
** be closed in different processes.
*/

int	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(philo->print);
	if (pthread_mutex_destroy(philo->print))
		return (error_message("Error pthread_mutex_destroy"));
	while (i < philo->value[0])
	{
		if (pthread_mutex_destroy((philo + i)->right_fork))
			return (error_message("Error pthread_mutex_destroy"));
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
** Tracks the death of the philosopher and prints the status
*/

static int	somebody_died(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->value[1])
	{
		ft_print(philo, DIED);
		return (1);
	}
	return (0);
}

/*
** The stream that passes through all the philosophers and 
** checks whether they died or not, if they died changes, 
** and also looks at how many philosophers are already full. 
** If everyone is full, the value[1] changes and the philosophers 
** stop their cycle
*/

void	*ft_undertaker(void *thread)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)thread;
	while (1)
	{
		i = 0;
		while (i < philo->value[0])
		{
			if (somebody_died(&philo[i]))
				return (NULL);
			if (philo[i].meal_numbers != NOT_EXIST)
			{
				if (philo->value[ARG6 - 1] == philo->value[0])
				{
					philo->value[1] = STOP_RUN;
					return (NULL);
				}
			}
			i++;
		}
	}
	return (NULL);
}

/*
** We block the forks, print the actions, check whether the
** philosophers should eat any number of times (check 
** whether the philosopher is full or not), record the start
** time of the meal, unlock the forks.
*/

static void	lock_unlock_fork(t_philo *philo, int action)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		philo->last_meal = get_time();
		ft_print(philo, FORK);
		ft_print(philo, EAT);
		if (philo->meal_numbers != NOT_EXIST)
			philo->meal_numbers -= 1;
		if (philo->meal_numbers == 0)
			philo->value[ARG6 - 1] += 1;
	}
	else if (action == UNLOCK)
	{	
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}	
}

/*
** In order for there to be no deadlock for sure, although we first
** created even and then odd philosophers, let's say that the non-
** even ones slept a little more while the even ones eat. If the 
** philosopher is 1, then we do not let him into the loop, because 
** he will block for 2 forks and will not return control to the main 
** thread. If the philosopher died or everyone ate, we write a flag in 
** value[1] that says it's time to close the streams
*/

void	*run_philo(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->num_philo % 2 == 0)
		thread_sleep(philo, (long)(philo->value[2] / 2));
	while (philo->value[1] != STOP_RUN && philo->value[0] != 1)
	{
		lock_unlock_fork(philo, LOCK);
		thread_sleep(philo, philo->value[2]);
		lock_unlock_fork(philo, UNLOCK);
		ft_print(philo, SLEEP);
		thread_sleep(philo, philo->value[3]);
		ft_print(philo, THINK);
	}
	return (NULL);
}

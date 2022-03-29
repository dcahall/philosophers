/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/28 20:27:38 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->value[0])
	{
		if (pthread_mutex_destroy((philo + i)->right_fork))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	somebody_died(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->value[1])
	{
		ft_print(philo, DIED);
		return (1);
	}
	return (0);
}

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

static void	lock_unlock_fork(t_philo *philo, int action)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, FORK);
		ft_print(philo, EAT);
		if (philo->meal_numbers != NOT_EXIST)
			philo->meal_numbers -= 1;
		if (philo->meal_numbers == 0)
			philo->value[ARG6 - 1] += 1;
		philo->last_meal = get_time();
	}
	else if (action == UNLOCK)
	{	
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}	
}

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

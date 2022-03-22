/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/22 16:29:09 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


// int	mutex_destroy(t_philo *philo, int *value)
// {
// 	int	i;

// 	i = 0;
// 	while (i < value[0])
// 	{
// 		if (pthread_mutex_destroy(philo[i].right_fork))
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

static void	lock_unlock_fork(t_philo *philo, int action)
{
	if (action == LOCK && philo->common->stop_run == NO) /*Нужно обращаться не к value[4] а к arg6*/
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, FORK);
		ft_print(philo, EAT);
		if (philo->meal_numbers)
			philo->meal_numbers -= 1;
		philo->last_meal = get_time() - philo->time_start;
	}
	else if (action == UNLOCK)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}	
}

static void	*run_philo(void *thread)
{
	t_philo	*philo;
	philo = (t_philo *)thread;

	philo->last_meal = 0;
	while (philo->common->stop_run == NO && philo->common->value[0] != 1)
	{
		ft_print(philo, THINK);
		lock_unlock_fork(philo, LOCK);
		thread_sleep(philo, EAT);
		lock_unlock_fork(philo, UNLOCK);
		ft_print(philo, SLEEP);
		thread_sleep(philo, SLEEP);
	}
	return (NULL);
}

static int pthread_create_wait(t_philo *philo, pthread_t *tid)
{
	int	i;
	
	i = 0;
	while (i < philo->common->value[0])
	{
		if (pthread_create(&tid[i], NULL, run_philo, (void *)(philo + i)) != 0)
			return (error_message("Error pthread_create (pthread_create_wait"));
		i += 2;
		if (i >= philo->common->value[0] && i % 2 == 0)
		{
			usleep(50);
			i = 1;
		}
	}
	if (ft_undertaker(philo) == ERROR)
		return (ERROR);
	i = philo->common->value[0];
	while (i--)
		if (pthread_join(philo->common->all_tid[i], NULL))
			return (error_message("Error pthread_join (pthread_create_wait)"));
	return (SUCCESS);
}

int	start_philo(t_philo *philo)
{
	int	result;

	result = pthread_create_wait(philo, philo->common->all_tid);
		// mutex_destroy(philo, value);
		ft_free(philo, philo->common);
	return (result);
}

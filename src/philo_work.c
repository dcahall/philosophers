/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/21 20:46:56 by dcahall          ###   ########.fr       */
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
	if (action == LOCK && philo->common->all_alive == YES)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, FIRST_FORK);
		pthread_mutex_lock(philo->right_fork);
		if (philo->arg6 == EXIST)
			philo->meal_numbers += 1;
		philo->last_meal = get_time();
		ft_print(philo, SECOND_FORK);
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

	while (philo->common->all_alive == YES && philo->common->value[0] != 1)
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
			usleep(30);
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

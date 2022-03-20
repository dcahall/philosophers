/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/20 17:59:59 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_print(t_philo *philo, int name_proccess)
{
	if (name_proccess == SECOND_FORK || name_proccess == FIRST_FORK)
	{
		printf("%ld %d has taken a fork\n", get_time() - \
			philo->time_start, philo->num_philo);
		if (name_proccess == SECOND_FORK)
		{
			printf("%ld %d is eating\n", get_time() - \
				philo->time_start, philo->num_philo);
		}
	}
	else if (name_proccess == SLEEP)
		printf("%ld %d is sleeping\n", get_time() - \
			philo->time_start, philo->num_philo);
	else if (name_proccess == THINK)
		printf("%ld %d is thinking\n", get_time() - \
			philo->time_start, philo->num_philo);
	else if (name_proccess == DIED)
		printf("%ld %d is sleeping\n", get_time() - \
			philo->time_start, philo->num_philo);
}

static void	lock_unlock_fork(t_philo *philo, int action)
{
	if (action == LOCK)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, FIRST_FORK);
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, SECOND_FORK);
		if (philo->arg6 == EXIST)
			philo->meal_numbers += 1;
	}
	else if (action == UNLOCK)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}	
}

void	*run_philo(void *tid)
{
	t_philo	*philo;
	int		i;
	philo = (t_philo *)tid;

	i = 1;
	while (i > 0)
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
	// tid = NULL;
	while (i < philo->common->value[0])
	{
		// printf("%d\n", i);
		if (pthread_create(&tid[i], NULL, run_philo, (void *)(philo + i)) != 0)
			return (ERROR);
		i += 2;
		if (i >= philo->common->value[0] && i % 2 == 0)
		{
			usleep(30);
			i = 1;
		}
	}
	i = philo->common->value[0];
	while (i)
	{
		i--;
		if (pthread_join(philo->common->all_tid[i], NULL) != 0)
			return (ERROR);
	}
	return (SUCCESS);
}

int	start_philo(t_philo *philo)
{
	if (pthread_create_wait(philo, philo->common->all_tid) == ERROR)
	{
		// mutex_destroy(philo, value);
		// return (ft_free(philo, philo->common));
	}
	// if (mutex_destroy(philo, value) == ERROR)
		// return (ERROR);
	return (SUCCESS);
}

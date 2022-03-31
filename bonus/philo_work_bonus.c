/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/31 19:54:46 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*somebody_died(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	// printf("philo #%d time = %ld\n", philo->num_philo, (get_time() - philo->last_meal));
	while (1)
	{
		if (get_time() - philo->last_meal > philo->value[1])
		{
			ft_print(philo, DIED);
			sem_post(philo->stop_run);
			return (NULL);
		}
	}
	return (NULL);
}

static void	lock_unlock_fork(t_philo *philo, int action)
{
	if (action == LOCK)
	{
		sem_wait(philo->forks);
		ft_print(philo, FORK);
		sem_wait(philo->forks);
		ft_print(philo, FORK);
		ft_print(philo, EAT);
		if (philo->meal_numbers != NOT_EXIST)
			philo->meal_numbers -= 1;
		if (philo->meal_numbers == 0)
			sem_post(philo->all_full);
		philo->last_meal = get_time();
	}
	else if (action == UNLOCK)
	{	
		sem_post(philo->forks);
		sem_post(philo->forks);
	}	
}

void	philo_proccess(t_philo *philo, int i)
{
	pthread_t	tid;

	philo->num_philo = i + 1;
	philo->time_start = get_time();
	philo->last_meal = philo->time_start;
	if (pthread_create(&tid, NULL, somebody_died, (void *)philo))
	{
		error_message("Error pthread_create(philo_proccess)");
		sem_post(philo->stop_run);
		exit(1);
	}
	if (pthread_detach(tid))
	{
		error_message("Error pthread_detach(philo_proccess)");
		sem_post(philo->stop_run);
		exit(1);
	}
	if (philo->num_philo % 2 == 0)
		thread_sleep((long)(philo->value[2] / 2));
	while (philo->value[0] != 1)
	{
		lock_unlock_fork(philo, LOCK);
		thread_sleep(philo->value[2]);
		lock_unlock_fork(philo, UNLOCK);
		ft_print(philo, SLEEP);
		thread_sleep(philo->value[3]);
		ft_print(philo, THINK);
	}
	exit(EXIT_SUCCESS);
}

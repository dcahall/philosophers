/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/04/02 12:34:19 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
** Checking the death of the philosopher, if he is dead, we
** return control to the main process
*/

static void	*somebody_died(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
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

/*
** Fork lock and unlock function. We also track how many 
** times the philosopher has eaten, if he is full, we unlock the 
** all_full semaphore
*/

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

/*
** We also create an unlink stream in order not to wait for it
** and philosophers began to eat think and sleep
*/

static void	check_death_thread(t_philo *philo)
{
	pthread_t	tid;

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
}

/*
** A thread is being created to track the philosopher's death.
** Until all the philosophers are created, the rest will wait for 
** them on the all_start semaphore. In order to avoid 
** deadlock, we create a launch sequence, for this even-
** numbered ones sleep half of the time that odd ones eat.
** Philosophers begin to eat sleep and think.
*/

void	philo_proccess(t_philo *philo, int i)
{
	check_death_thread(philo);
	philo->num_philo = i + 1;
	sem_wait(philo->all_start);
	philo->time_start = get_time();
	philo->last_meal = philo->time_start;
	if (philo->num_philo % 2 == 0)
		thread_sleep((long)(philo->value[2] / 2));
	while (1)
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

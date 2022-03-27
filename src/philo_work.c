/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/27 21:10:49 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	mutex_destroy(t_common *common)
// {
// 	int	i;

// 	i = 0;
// 	while (i < common->value[0])
// 	{
// 		if (pthread_mutex_destroy(&common->all_forks[i]))
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }


static int	somebody_died(t_philo *philo)
{
	if (philo->last_meal)
		if (get_time() - philo->last_meal > philo->value[1])
		{
			printf("OK %ld\n", philo->last_meal);
			ft_print(philo, DIED);
			return (1);
		}
	return (0);
}

void *ft_undertaker(void *thread)
{
	t_philo	*philo;
	int		all_full;
	int		i;

	philo = (t_philo *)thread;
	while (1)
	{
		i = 0;
		all_full = 0;
		while (i < philo->value[0])
		{
			if (somebody_died(&philo[i]))
				return (NULL);
			if (philo[i].meal_numbers != NOT_EXIST)
				if (philo->meal_numbers <= 0)
					all_full += 1;
			i++;
		}
		if (all_full == philo->value[0])
			return (NULL);
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
	philo->time_start = get_time();
	philo->last_meal = 0;
	while (philo->value[1] != STOP_RUN && philo->value[0] != 1)
	{
		ft_print(philo, THINK);
		lock_unlock_fork(philo, LOCK);
		thread_sleep(philo, philo->value[2]);
		lock_unlock_fork(philo, UNLOCK);
		ft_print(philo, SLEEP);
		thread_sleep(philo, philo->value[3]);
	}
	return (NULL);
}

// static void takeFork(t_philo *philo, int forks) {
//     if (forks == LOCK) {
//         pthread_mutex_lock(philo->left_fork);
//         pthread_mutex_lock(philo->right_fork);
//     } else {
//         pthread_mutex_unlock(philo->left_fork);
//         pthread_mutex_unlock(philo->right_fork);
//     }
// }

// static void printStatus(t_philo *philo, int status) {
//     long time;

//     time = get_time();
//     if (status == EAT && philo->value[1]) {
//         printf("%li\t%d has taken a fork\n", time - philo->time_start, philo->num_philo);
//         printf("%li\t%d is eating\n", time - philo->time_start, philo->num_philo);
//         if (philo->meal_numbers != NOT_EXIST)
//             philo->meal_numbers--;
        
//     } else if (status == SLEEP && philo->value[1]) {
//         printf("%li\t%d is sleeping\n", time - philo->time_start, philo->num_philo);
// 		thread_sleep(philo, philo->value[3]);
//         if (philo->value[1])
//             printf("%li\t%d is thinking\n", time - philo->time_start, philo->num_philo);
//     }
// }

// void	*run_philo(void *thread)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)thread;
// 	philo->time_start = get_time();
// 	philo->last_meal = 0;
// 	while (philo->value[1] != STOP_RUN && philo->value[0] != 1)
// 	{
//         takeFork(philo, LOCK);
//         philo->last_meal = get_time();
//         printStatus(philo, EAT);
//         takeFork(philo, UNLOCK);
//         printStatus(philo, SLEEP);
// 	}
// 	return (NULL);
// }

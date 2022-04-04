/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 18:06:07 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* 
** The function returns the current time in milliseconds.
*/

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

/*
** Functions responsible for sleep thread
*/

void	thread_sleep(t_philo *philo, long millisecond)
{
	long	time;

	time = get_time() + millisecond;
	while (time > get_time() && philo->value[1] != STOP_RUN)
		usleep(300);
}

/*
** The output function, the mutex is needed so that the 
** output is not mixed. If the philosopher has died, then he 
** raises the flag stored in philo->value[1] and informs 
** others about it. This avoids any output to the console
** after the philosopher's death.
*/

void	ft_print(t_philo *philo, int name_proccess)
{
	long	time;

	pthread_mutex_lock(philo->print);
	if (philo->value[1] == STOP_RUN)
	{	
		pthread_mutex_unlock(philo->print);
		return ;
	}
	time = get_time();
	printf("%ld %d ", time - philo->time_start, philo->num_philo);
	if (name_proccess == FORK)
		printf("has taken a fork\n");
	if (name_proccess == EAT)
		printf("is eating\n");
	else if (name_proccess == SLEEP)
		printf("is sleeping\n");
	else if (name_proccess == THINK)
		printf("is thinking\n");
	else if (name_proccess == DIED)
	{
		philo->value[1] = STOP_RUN;
		printf("is died\n");
	}
	pthread_mutex_unlock(philo->print);
}

/*
** The function frees up all allocated memory under the 
** philosopher (input parameters, mutexes, thread IDs)
*/

int	ft_free(int *value, t_philo *philo, pthread_t *tid, pthread_mutex_t *print)
{
	if (philo)
	{
		if (philo->right_fork)
			free(philo->right_fork);
		free(philo);
	}
	if (tid)
		free(tid);
	if (value)
		free(value);
	if (print)
		free(print);
	return (EXIT_FAILURE);
}

int	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	return (EXIT_FAILURE);
}

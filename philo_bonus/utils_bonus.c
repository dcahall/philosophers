/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 16:21:03 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	thread_sleep(long millisecond)
{
	long	time;

	time = get_time() + millisecond;
	while (time > get_time())
		usleep(300);
}

/*
** The semaphore is needed in order for the output to be mixed
** If the philosopher is dead, the semaphore is not unblocked 
** so that others stop typing
*/

void	ft_print(t_philo *philo, int name_proccess)
{
	long	time;

	sem_wait(philo->print);
	time = get_time();
	printf("%ld %d ", time - philo->time_start, philo->num_philo);
	if (name_proccess == FORK)
		printf("has taken a fork\n");
	else if (name_proccess == EAT)
		printf("is eating\n");
	else if (name_proccess == SLEEP)
		printf("is sleeping\n");
	else if (name_proccess == THINK)
		printf("is thinking\n");
	else if (name_proccess == DIED)
	{
		printf("is died\n");
		return ;
	}
	sem_post(philo->print);
}

int	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	return (EXIT_FAILURE);
}

/*
** The function clears all allocated memory,
** and also kills processes-philosophers.
** The lifetime of the named semaphore is longer than the 
** program, so you need to delete its name, and when you 
** close the program, the semaphore will close
*/

int	ft_free(int *value, t_philo *philo, pid_t *pid)
{
	int	i;

	i = 0;
	if (pid)
	{
		while (i < value[0])
		{
			kill(pid[i], SIGTERM);
			i++;
		}
		free(pid);
	}
	if (philo)
	{
		sem_unlink("/forks");
		sem_unlink("/all_full");
		sem_unlink("/print");
		sem_unlink("/stop_run");
		free(philo);
	}
	if (value)
		free(value);
	return (EXIT_FAILURE);
}

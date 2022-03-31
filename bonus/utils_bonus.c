/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/31 19:56:59 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	thread_sleep(long millisecond)
{
	long	time;

	time = get_time() + millisecond;
	while (time > get_time())
		usleep(300);
}

void	ft_print(t_philo *philo, int name_proccess)
{
	long	time;

	sem_wait(philo->print);
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
		printf("is died\n");
	sem_post(philo->print);
}

int	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	return (EXIT_FAILURE);
}

int	ft_free(int *value, t_philo *philo, pid_t *pid)
{
	int	i;

	i = 0;
	printf("GG WP2\n");
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
		// sem_close(philo->forks);
		// sem_close(philo->print);
		// sem_close(philo->stop_run); /*возможно нужно сначала отвзять*/
		// sem_close(philo->all_full);
		free(philo);
	}
	if (value)
		free(value);

	return (EXIT_FAILURE);
}
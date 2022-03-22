/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/22 16:20:25 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1e3 + current_time.tv_usec * 1e-3);
}

void	thread_sleep(t_philo *philo, int action_status)
{
	int		millisecond;
	long	time;

	if (action_status == SLEEP)
		millisecond = philo->common->value[3];
	else
		millisecond = philo->common->value[2];
	time = get_time();
	while (get_time() - time < millisecond && philo->common->stop_run == NO)
		usleep(10);
}

void	ft_print(t_philo *philo, int name_proccess)
{
	long	time;

	pthread_mutex_lock(philo->common->stop_print);
	if (philo->common->stop_run == YES)
	{	
		pthread_mutex_unlock(philo->common->stop_print);
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
		philo->common->stop_run = YES;
		printf("is died\n");
	}
	pthread_mutex_unlock(philo->common->stop_print);
}

void	ft_free(t_philo *philo, t_common *common)
{
	if (common)
	{
		if (common->all_forks)
			free(common->all_forks);
		if (common->all_tid)
			free(common->all_tid);
		if (common->value)
			free(common->value);
		if (common->stop_print)
			free(common->stop_print);
		free(common);
	}
	if (philo)
		free(philo);
}

int	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	return (ERROR);
}
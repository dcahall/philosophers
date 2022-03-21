/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/21 19:50:42 by dcahall          ###   ########.fr       */
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

	if (philo->common->all_alive == NO)
		return ;
	if (action_status == SLEEP)
		millisecond = philo->common->value[3];
	else
		millisecond = philo->common->value[2];
	time = get_time();
	while (get_time() - time < millisecond)
		usleep(100);
}

void	ft_print(t_philo *philo, int name_proccess)
{
	if (philo->common->all_alive == NO)
		return ;
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
		printf("%ld %d is died\n", get_time() - \
			philo->time_start, philo->num_philo);
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
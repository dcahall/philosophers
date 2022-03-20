/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:44:56 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/20 18:25:25 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1e3 + current_time.tv_usec * 1e-3);
}

int	ft_free(t_philo *philo, t_common *common)
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
	return (ERROR);
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
	while (get_time() - time < millisecond)
		usleep(100);
}

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

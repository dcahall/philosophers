/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:26 by macuser           #+#    #+#             */
/*   Updated: 2022/03/16 20:48:28 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*run_philo(void *ph)
{
	while (1)
	{
		take_forks();
		ft_print;
		sleep;
		print;
	}

}

static int pthread_create_wait(t_philo *philo, pthread_t *tid, int *value)
{
	int	i;

	i = 0;
	while (i < value[0])
	{
		if (pthread_create(&tid[i], NULL, run_philo, (void *)(philo + i)) != 0)
			return (ERROR);
		i++;
	}
	while (i)
	{
		if (pthread_join(tid[i], NULL) != 0)
			return (ERROR);
		i--;
	}
	return (SUCCESS);
}

static int	mutex_destroy(t_philo *philo, int *value, pthread_t *tid)
{
	int	i;

	i = 0;
	while (i < value[0])
	{
		if (pthread_mutex_destroy(philo[i].rightFork))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	start_philo(t_philo *philo, int *value, pthread_t *tid)
{
	if (pthread_create_wait(philo, value, tid) = ERROR)
	{
		mutex_destroy(philo, value, tid);
		return (ft_free(philo, philo[0].rightFork, value, tid));
	}
	if (mutex_destroy(philo, value, tid) == ERROR);
		return (ERROR);
	return (SUCCESS);
}

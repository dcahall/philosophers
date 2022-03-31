/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:21:53 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/31 19:55:03 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	init_sem(t_philo *philo, int *value)
{
	sem_unlink("/forks");
	sem_unlink("/all_full");
	sem_unlink("/print");
	sem_unlink("/stop_run");
	philo->forks = sem_open("/forks", O_CREAT | O_EXCL, 0666, value[0]);
	philo->print = sem_open("/print", O_CREAT | O_EXCL, 0666, 1);
	philo->all_full = sem_open("/all_full", O_CREAT | O_EXCL, 0666, 0);
	philo->stop_run = sem_open("/stop_run", O_CREAT | O_EXCL, 0666, 0);
	if (philo->forks == SEM_FAILED || philo->print == SEM_FAILED
		|| philo->all_full == SEM_FAILED || philo->stop_run == SEM_FAILED)
		return (error_message("Error sem_open"));
	return (EXIT_SUCCESS);
}

static t_philo	*init_ph(int *value, int argc)
{
	t_philo			*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	if (init_sem(philo, value) == EXIT_FAILURE)
	{
		free(philo);
		return (NULL);
	}
	philo->value = value;
	if (argc == ARG6)
		philo->meal_numbers = value[4];
	else
		philo->meal_numbers = NOT_EXIST;
	return (philo);
}

/*	непонятно с какими семафорами работать 
** 	1. просто разблокируем семафор stop_run,
** 	и основной процесс начинает всех убивать
**
**  2. Cначала заблокировать семафор на печать
**	а потом только разблокировать stop_run
**	но в этом случае придется лишнего постоять
**	на блокировке семафора печати
*/
static void *meals_counter(void *thread)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = (t_philo *)thread;
	while (i < philo->value[0])
	{
		sem_wait(philo->all_full);
		i++;
	}
	sem_wait(philo->print);
	sem_post(philo->stop_run);
	return (NULL);
}



/* Создаем отвязанный поток, который следит за количеством сытых
** философов. Затем создаем процессы философы. Чтобы главный процесс
** не завершился блокируем его на stop run.
*/
static int	create_process(t_philo *philo, pid_t *pid, int *value)
{
	pthread_t	tid;
	int			i;

	i = 0;
	if (pthread_create(&tid, NULL, meals_counter, (void *)philo))
		return (error_message("Error pthread_create (create_process"));
	if (pthread_detach(tid))
		return (error_message("Error pthread_detach (create_process"));
	while (i < value[0])
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error_message("Error fork");
		else if (pid[i] == 0)
			philo_proccess(philo, i);
		i++;
	}
	sem_wait(philo->stop_run);
	printf("GG WP\n");
	ft_free(value, philo, pid);
	return (EXIT_SUCCESS);
}

int	ft_init(int *value, int argc)
{
	t_philo	*philo;
	pid_t	*pid;

	philo = init_ph(value, argc);
	if (!philo)
		return (ft_free(value, NULL, NULL));
	pid = malloc(sizeof(pid_t) * value[0]);
	if (!pid)
		return (ft_free(value, philo, NULL));
	if (create_process(philo, pid, value) == EXIT_FAILURE)
		return (ft_free(value, philo, pid));
	return (EXIT_SUCCESS);
}

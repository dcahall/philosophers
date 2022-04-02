/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:25:25 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 16:06:30 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h> 
# include <sys/types.h>
# include <signal.h>
# include <semaphore.h>
# include <errno.h>
# define CONTINUE		1
# define STOP_RUN		-1
# define NOT_EXIST		-1
# define EXIST			0
# define ARG6			6
# define FORK			10
# define EAT			11
# define SLEEP			12
# define THINK			13
# define DIED			14
# define LOCK			15
# define UNLOCK			16
# define CHILD_PROCCESS	0

typedef struct philo
{
	int		*value;
	int		num_philo;
	long	last_meal;
	long	time_start;
	int		meal_numbers;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*all_full;
	sem_t	*stop_run;
	sem_t	*all_start;
}	t_philo;

int		*parse_arg(int argc, char **argv);
int		ft_init(int *value, int argc);

int		ft_free(int *value, t_philo *philo, pid_t *pid);
int		error_message(char *message);
long	get_time(void);
void	ft_print(t_philo *philo, int name_proccess);
void	thread_sleep(long millisecond);

void	philo_proccess(t_philo *philo, int i);

#endif

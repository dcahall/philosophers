/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:10:00 by dcahall           #+#    #+#             */
/*   Updated: 2022/04/02 16:14:48 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
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

typedef struct philo
{
	int				*value;
	int				num_philo;
	long			last_meal;
	long			time_start;
	int				meal_numbers;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
}	t_philo;

int		*parse_arg(int argc, char **argv);
int		ft_init(int *value, int argc);

int		ft_free(int *value, t_philo *philo, pthread_t *tid, \
		pthread_mutex_t *print);
int		error_message(char *message);
long	get_time(void);
void	ft_print(t_philo *philo, int name_proccess);
void	thread_sleep(t_philo *philo, long millisecond);

void	*ft_undertaker(void *thread);
void	*run_philo(void *thread);
int		mutex_destroy(t_philo *philo);

#endif

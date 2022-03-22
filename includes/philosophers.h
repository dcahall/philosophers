/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:20:17 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/22 16:27:52 by dcahall          ###   ########.fr       */
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
# define ERROR			1
# define SUCCESS		0
# define ARG6			6
# define FORK			10
# define EAT			11
# define SLEEP			12
# define THINK			13
# define DIED			14
# define LOCK			15
# define UNLOCK			16
# define NOT_EXIST		17
# define YES			18
# define NO				19

typedef struct common_data
{
	int				*value;
	int				stop_run;
	pthread_mutex_t	*stop_print;
	pthread_mutex_t	*all_forks;
	pthread_t		*all_tid;
}	t_common;

typedef struct philo
{
	int				num_philo;
	long			last_meal;
	long			time_start;
	int				meal_numbers;
	t_common		*common;	
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		*parse_arg(int argc, char **argv);
int		ft_init(int *value, int argc);

void	thread_sleep(t_philo *philo, int action_status);
void	ft_free(t_philo *philo, t_common *common);
void	ft_print(t_philo *philo, int name_proccess);
int		error_message(char *message);
long	get_time(void);

int		start_philo(t_philo *philo);
int		ft_undertaker(t_philo *all_philo);

#endif

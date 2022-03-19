/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:20:17 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/19 20:25:40 by dcahall          ###   ########.fr       */
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
# define ARG6			6
# define EXIST			1
# define NOT_EXIST		0
# define ERROR			1
# define SUCCESS		0
# define FIRST_FORK		10
# define SECOND_FORK	11
# define EAT			12
# define SLEEP			13
# define THINK			14
# define DIED			15
# define LOCK			16
# define UNLOCK			17

typedef struct common_data
{
	long			time_start;
	int				*value;
	pthread_mutex_t	*all_forks;
	pthread_mutex_t	*access_print;
	pthread_t		*all_tid;
}	t_common;

typedef struct philo
{
	int				num_philo;
	int				arg6;
	long			last_meal;
	int				meal_numbers
	t_common		*common;	
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		*parse_arg(int argc, char **argv);
int		ft_init(int *value, int argc);

long	get_time(void);
int		mutex_destroy(t_philo *philo, int *value);
int		ft_free(t_philo *philo, t_common *common);

int		start_philo(t_philo *philo);

#endif

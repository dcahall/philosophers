/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:20:17 by dcahall           #+#    #+#             */
/*   Updated: 2022/03/16 20:27:36 by dcahall          ###   ########.fr       */
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
# define ARG6		6
# define EXIST		1
# define NOT_EXIST	0
# define ERROR		1
# define SUCCESS	0

typedef struct philo 
{
	int	*value;
	int	num_philo;
	int	arg6;
	long time;
	pthread_mutex_t	*accessForks;
	pthread_mutex_t	*leftFork;
	pthread_mutex_t	*rightFork;
}	t_philo;

int		*parse_arg(int argc, char **argv);
int		start_philo(t_philo *philo, int *value, pthread_t *tid);
int		ft_free(t_philo *philo, pthread_mutex_t *forks ,int *value, pthread_t	*tid);
int		ft_init(int *value, int argc);
long	get_time(void);

#endif

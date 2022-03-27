#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "../libft/libft.h"
#include <sys/time.h>
#include <pthread.h>

// void *ft_print(void *ps)
// {
// 	ps = NULL;
// 	for(int i = 0; i < 10000000; i++)
// 	{
// 	}
// 	printf("tid1: [%u]\n", (int)pthread_self());
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t	*tid;
// 	int 		i;

// 	i = 0;
// 	tid = malloc(sizeof(tid) * 5);
// 	if (!tid)
// 		return (1);
// 	while (i < 5)
// 	{
// 		pthread_create((tid + i), NULL, ft_print, NULL);
// 		i++;
// 		printf("tid: [%u]\n", (int)pthread_self());
// 	}
// 	for (i = 0; i < 5; i++)
// 	{
// 		// printf("tid2: [%u]\n", (int)pthread_self());
// 		pthread_join(tid[i], NULL);
// 	}
// }

/**********************************************************/

// long	get_time(void)
// {
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	return (current_time.tv_sec * 1e3 + current_time.tv_usec * 1e-3);
// }

// void	ft_sleep(int milisec)
// {
// 	while (milisec)
// 	{
// 		milisec--;
// 		usleep(1000);
// 	}
// }

// void	smart_sleep(int milisec)
// {
// 	long	time_start;

// 	time_start = get_time();
// 	while (get_time() - time_start < milisec)
// 		usleep(100);
// }

// int main(void)
// {
// 	long	time_start;
// 	long	time_stop;

// 	time_start = get_time();
// 	// ft_sleep(1000);
// 	smart_sleep(1000);
// 	time_stop = get_time();
// 	printf("time: %ld", time_stop - time_start);
// }

/*************************************************************/

// pthread_mutex_t mutex;

// long	get_time(void)
// {
// 	struct timeval	current_time;

// 	gettimeofday(&current_time, NULL);
// 	return (current_time.tv_sec * 1e3 + current_time.tv_usec * 1e-3);
// }

// void	*smart_sleep(void *time)
// {
// 	long	time_start;
// 	int		milisec;

// 	pthread_mutex_lock(&mutex);
// 	sleep(2);
// 	milisec = *(int *)time;
// 	time_start = get_time();
// 	while (get_time() - time_start < milisec)
// 		usleep(100);
// 	printf("mutex unlock #2: %d\n", pthread_mutex_unlock(&mutex));
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t	tid;
// 	int			milisec;

// 	milisec = 1000;
// 	pthread_mutex_init(&mutex, NULL);
// 	printf("create:%d\n", pthread_create(&tid, NULL, smart_sleep, (void *)&milisec));
// 	usleep(20000);
// 	printf("mutex_unlock: %d\n", pthread_mutex_unlock(&mutex));
// 	printf("join %d\n", pthread_join(tid, NULL));
// }

/*************************************************************/


// int main(void)
// {
// 	int	i;

// 	i = 10;
// 	printf("%d\n", i);
// 	while (i--)
// 		printf("%d\n", i);
// }
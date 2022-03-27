#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include "../libft/libft.h"
#include <sys/time.h>
#include <pthread.h>

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec * 1e-3);
}

void	thread_sleep(int milliseconds)
{
	long	time;
	long	time_stop;

	time = get_time();
	while (milliseconds)
	{
		usleep(1000);
		milliseconds--;
	}
	time_stop = get_time();
	printf("time runnig: %ld\n", time_stop - time);
}

int main()
{
	thread_sleep(100);
	// long time;
	// time = get_time();
	// usleep(10000);
	// printf("%ld\n", get_time() - time);
}

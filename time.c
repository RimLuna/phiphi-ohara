#include "philo.h"

unsigned long	gettime(void)
{
	struct timeval	time;
	unsigned long	t;

	gettimeofday(&time, NULL);
	t = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (t);
}

void	_usleep(int miliseconds)
{
	unsigned long	time;

	time = gettime();
	while (gettime() < time + miliseconds)
		usleep(50);
}

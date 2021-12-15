#include "philo.h"

int	oddthreads(t_philo *p)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < p[0].sim->count)
	{
		if (i % 2 == 1)
		{
			if (pthread_create(&thread, NULL, routine, &p[i]) != 0)
				return (-1);
			usleep(50);
		}
		i++;
	}
	return (1);
}

int	eventhreads(t_philo *p)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < p[0].sim->count)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&thread, NULL, routine, &p[i]) != 0)
				return (-1);
			usleep(50);
		}
		i++;
	}
	return (1);
}

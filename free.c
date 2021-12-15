#include "philo.h"

void	free_mutex(t_sim *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->count)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&sim->print);
	pthread_mutex_destroy(&sim->check_dead);
	pthread_mutex_destroy(&sim->check_meals);
}

void	free_sim(t_sim *sim)
{
	if (sim)
	{
		free(sim->forks);
		free(sim->p);
	}
}

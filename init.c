#include "philo.h"

int	init_threads(t_philo *p)
{
	if (eventhreads(p) < 0)
		return (-1);
	if (oddthreads(p) < 0)
		return (-1);
	return (1);
}

int	init_mutex(pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	sim->p = malloc(sizeof(t_philo) * sim->count);
	if (!sim->p)
		return (-1);
	while (i < sim->count)
	{
		sim->p[i].sim = sim;
		sim->p[i].lfork = i;
		sim->p[i].rfork = (i + 1) % sim->count;
		sim->p[i].p_id = i + 1;
		sim->p[i].eat_count = 0;
		sim->p[i].is_eating = 0;
		sim->p[i].is_dead = 0;
		sim->p[i].ate_enough = 0;
		i++;
	}
	sim->time_start = gettime();
	sim->dead = 0;
	return (1);
}

int	siminit(t_sim *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (-1);
	if (init_mutex(sim->forks, sim->count) < 0)
		return (-1);
	if (pthread_mutex_init(&sim->print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&sim->check_dead, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&sim->check_meals, NULL) != 0)
		return (-1);
	if (init_philos(sim) < 0)
		return (-1);
	return (init_threads(sim->p));
}

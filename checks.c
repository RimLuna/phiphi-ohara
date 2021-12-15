#include "philo.h"

int	param_checks(t_sim *sim)
{
	if (sim->count <= 0 \
		|| sim->time_to_die <= 0 \
		|| sim->time_to_eat <= 0 \
		|| sim->time_to_sleep <= 0 \
		|| (sim->n_times_eat <= 0 && sim->n_times_eat != -1))
		return (_error("Arguments should be positive"));
	return (1);
}

int	arg_checks(t_sim *sim, char *argv[])
{
	if (!aredigits(argv[1]) || !aredigits(argv[2]) \
		|| !aredigits(argv[3]) || !aredigits(argv[4]))
		return (-1);
	if (argv[5])
	{
		if (!aredigits(argv[5]))
			return (-1);
	}
	sim->count = _atoi(argv[1]);
	sim->time_to_die = _atoi(argv[2]);
	sim->time_to_eat = _atoi(argv[3]);
	sim->time_to_sleep = _atoi(argv[4]);
	if (argv[5])
		sim->n_times_eat = _atoi(argv[5]);
	else
		sim->n_times_eat = -1;
	return (param_checks(sim));
}

int	life_checks(t_sim *sim, int i)
{
	pthread_mutex_lock(&sim->check_dead);
	if (!sim->p[i].is_eating \
		&& sim->p[i].time_last + sim->time_to_die < gettime())
	{
		sim->dead = 1;
		pthread_mutex_unlock(&sim->check_dead);
		return (0);
	}
	pthread_mutex_unlock(&sim->check_dead);
	return (1);
}

void	philo_checks(t_sim *sim)
{
	int	i;
	int	end;

	while (1)
	{
		i = 0;
		end = 0;
		while (i < sim->count)
		{
			if (!life_checks(sim, i))
			{
				print_message(sim, sim->p[i].p_id, DIED);
				return ;
			}
			if (sim->p[i].ate_enough)
				end++;
			if (end == sim->count)
			{
				print_message(sim, 0, ENOUGH);
				return ;
			}
			i++;
		}
	}
}

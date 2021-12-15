#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->lfork]);
	print_message(philo->sim, philo->p_id, FORK);
	pthread_mutex_lock(&philo->sim->forks[philo->rfork]);
	print_message(philo->sim, philo->p_id, FORK);
	philo->is_eating = 1;
	philo->time_last = gettime();
	print_message(philo->sim, philo->p_id, EAT);
	_usleep(philo->sim->time_to_eat);
	if (philo->sim->n_times_eat != -1)
		philo->eat_count++;
	if (philo->eat_count == philo->sim->n_times_eat)
		philo->ate_enough = 1;
	pthread_mutex_unlock(&philo->sim->forks[philo->rfork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->lfork]);
	philo->is_eating = 0;
}

void	sleep_think(t_philo *philo)
{
	print_message(philo->sim, philo->p_id, SLEEP);
	_usleep(philo->sim->time_to_sleep);
	print_message(philo->sim, philo->p_id, THINK);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->time_last = gettime();
	while (1)
	{
		pthread_mutex_lock(&philo->sim->check_dead);
		if (philo->sim->dead || philo->ate_enough)
		{
			pthread_mutex_unlock(&philo->sim->check_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->sim->check_dead);
		while (!philo->sim->dead && !philo->ate_enough)
		{
			eat(philo);
			sleep_think(philo);
		}
	}
	return (NULL);
}

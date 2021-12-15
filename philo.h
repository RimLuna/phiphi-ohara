#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define ERR_ARGS "invalid args"
# define ERR_INIT "init error"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define ENOUGH "meals count over"

typedef struct s_sim
{
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_eat;
	unsigned long		time_start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		check_dead;
	pthread_mutex_t		check_meals;
	int					dead;
	struct s_philo		*p;
}			t_sim;

typedef struct s_philo
{
	t_sim			*sim;
	int				lfork;
	int				rfork;
	unsigned long	time_start;
	unsigned long	time_last;
	int				is_eating;
	int				is_dead;
	int				ate_enough;
	int				eat_count;
	int				p_id;
}			t_philo;

int				aredigits(const char *str);
int				_error(const char *str);
int				_atoi(const char *str);
void			_usleep(int miliseconds);
void			print_message(t_sim *sim, int p_id, const char *str);
unsigned long	gettime(void);

int				arg_checks(t_sim *sim, char *argv[]);
int				siminit(t_sim *sim);
int				oddthreads(t_philo *p);
int				eventhreads(t_philo *p);
void			sleep_think(t_philo *philo);
void			*routine(void *args);
void			philo_checks(t_sim *sim);

void			free_mutex(t_sim *sim);
void			free_sim(t_sim *sim);

#endif

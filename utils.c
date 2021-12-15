#include "philo.h"

int	_error(const char *str)
{
	printf("%s\n", str);
	return (-1);
}

int	aredigits(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	_atoi(const char *str)
{
	int			digit;
	long int	res;

	res = 0;
	digit = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		digit = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str <= '9' && *str >= '0')
	{
		res *= 10;
		res += *str - '0';
		if (res > 2147483647 && digit == 1)
			return (-1);
		if (res > 2147483648 && digit == -1)
			return (0);
		str++;
	}
	return (res * digit);
}

void	print_message(t_sim *sim, int p_id, const char *str)
{
	pthread_mutex_lock(&sim->print);
	pthread_mutex_lock(&sim->check_dead);
	pthread_mutex_lock(&sim->check_meals);
	printf("%-10lu %-8d %s\n", gettime() - sim->time_start, p_id, str);
	if (str[0] == 'd' || str[0] == 'm')
	{
		pthread_mutex_unlock(&sim->check_meals);
		pthread_mutex_unlock(&sim->check_dead);
		return ;
	}
	pthread_mutex_unlock(&sim->check_meals);
	pthread_mutex_unlock(&sim->check_dead);
	pthread_mutex_unlock(&sim->print);
}

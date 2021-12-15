#include "philo.h"

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (argc != 5 && argc != 6)
		return (_error(USAGE));
	if (arg_checks(&sim, argv) < 0)
		return (_error(ERR_ARGS));
	if (siminit(&sim) < 0)
		return (_error(ERR_INIT));
	philo_checks(&sim);
	_usleep(500);
	free_mutex(&sim);
	free_sim(&sim);
	return (0);
}

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#include "philo.h"
#include "timestamp.h"
#include "xmutex.h"
#include "atoi_errcode.h"

void	ft_puterr(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write (2, s, len);
}

int	ft_init_shared(t_shared *shared, char **strargs)
{
	int	errcode;

	errcode = 0;
	// TODO change atoi to signed version
	shared->nphilo = ft_atoi_errcode(strargs[1], &errcode);
	shared->time_to_die = ft_atoi_errcode(strargs[2], &errcode);
	shared->time_to_eat = ft_atoi_errcode(strargs[3], &errcode);
	shared->time_to_sleep = ft_atoi_errcode(strargs[4], &errcode);
	if (strargs[5])
		shared->nmeals = ft_atoi_errcode(strargs[5], &errcode);
	if (errcode)
		return (1);
	shared->nsatiated = 0;
	pthread_mutex_init(&(shared->done_mutex), NULL);
	pthread_mutex_init(&(shared->fork_access), NULL);
	shared->done = FALSE;
}

void	ft_destroy_shared(t_shared *shared)
{
	pthread_mutex_destroy(&(shared->done_mutex));
	pthread_mutex_destroy(&(shared->fork_access));
}

void	ft_init_philo(t_philo *philo, int i, t_shared *shared, t_xmutex *forks)
{
	philo->index = i + 1;
	philo->times_eaten = 0;
	philo->last_ate = ft_timestamp(0);
	philo->shared = shared;
	philo->left_fork = forks + i;
	philo->right_fork = forks + ((i + 1) % shared->nphilo);
}

int	main(int ac, char **av)
{
	t_shared		shared;
	pthread_t		*threads;
	t_philo			*philos;
	t_xmutex		*forks;
	int				i;

	if (!(ac == 5 || ac == 6) || ft_init_shared(&shared, av) == 1)
	{
		ft_puterr("invalid arguments.\ncall with: ");
		ft_puterr("philosophers num_philo time_to_die eat sleep [num_meals]\n");
		return (1);
	}
	philos = malloc(sizeof(t_philo) * shared.nphilo);
	threads = malloc(sizeof(pthread_t) * shared.nphilo);
	forks = malloc(sizeof(t_xmutex) * shared.nphilo);
	i = 0;
	ft_timestamp(TS_RESET);
	while (i < shared.nphilo)
	{
		ft_init_philo(philos + i, i, &shared, forks);
		pthread_create(threads + i, NULL, ft_philo_routine, philos + i);
		++i;
	}
	while (!shared.done)
		usleep(500);
	i = 0;
	while (i < shared.nphilo)
		pthread_join(threads[i++], NULL);
	free(philos);
	free(threads);
	free(forks);
	ft_destroy_shared(&shared);
	return (0);
}

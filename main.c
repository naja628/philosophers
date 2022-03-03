#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "time_ops.h"
#include "philo.h"

// note freed by 'ft_init_philo'
t_data_wrap	*ft_new_arg(t_shared *shared, int id)
{
	t_data_wrap	*ret;

	ret = malloc(sizeof(t_data_wrap));
	if (!ret)
		// TODO error
		return (NULL);
	ret->shared = shared;
	ret->id = id;
	return (ret);
}

#include <stdio.h>
static void	ft_init_shared_resources(t_shared *shared, int ac, char **av)
{
	if (ac < 5 || 6 < ac)
		//TODO error
		return ;
	// TODO atoi -> ft_atoi
	// maybe use array? 
	shared->nphilo = atoi(av[1]);
	shared->timetoeat = atoi(av[2]);
	shared->timetosleep = atoi(av[3]);
	shared->timetodie = atoi(av[4]);
	shared->nmeals = -1;
	shared->first_blood = 0;
	printf("%d philos\n", shared->nphilo);
	if (ac == 6)
		shared->nmeals = atoi(av[5]);
	shared->fork_access = malloc(sizeof(pthread_mutex_t));
	shared->forks = malloc(shared->nphilo);
	if (!shared->fork_access | !shared->forks)
		// TODO error
		return ;
	memset(shared->forks, 1, shared->nphilo);
	if (pthread_mutex_init(shared->fork_access, NULL) != 0)
		// deal with error
		return ;
	return ;
}

static void	ft_destroy_shared(t_shared *shared)
{
	pthread_mutex_destroy(shared->fork_access);
	free(shared->fork_access);
	free(shared->forks);
}

int	main(int ac, char **av)
{
	t_shared	shared;
	int			i;
	pthread_t	*threads;
	t_data_wrap	*arg;

	ft_init_shared_resources(&shared, ac, av);
	// start chrono now
	ft_timestamp(1);
	i = 0;
	threads = malloc(sizeof(pthread_t) * shared.nphilo);
	while (i < shared.nphilo)
	{
		arg = ft_new_arg(&shared, i);
		pthread_create(threads + i, NULL, ft_philo, arg);
		++i;
		printf("philo was born \n");
	}
	// i don't think we need this cuz join auto-waits
//	while (!shared->first_blood)
//		usleep(TIME_ATOM);
	i = 0;
	while (i < shared.nphilo)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	ft_destroy_shared(&shared);
	return (0);
}

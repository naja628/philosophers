/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:46 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:20:46 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#include "philo.h"
#include "timestamp.h"
#include "xmutex.h"
#include "atoi_errcode.h"
#include "launch_threads.h"

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
	shared->nphilo = ft_positive_atoi_errcode(strargs[1], &errcode);
	shared->time_to_die = ft_positive_atoi_errcode(strargs[2], &errcode);
	shared->time_to_eat = ft_positive_atoi_errcode(strargs[3], &errcode);
	shared->time_to_sleep = ft_positive_atoi_errcode(strargs[4], &errcode);
	if (strargs[5])
		shared->nmeals = ft_positive_atoi_errcode(strargs[5], &errcode);
	if (errcode)
		return (-1);
	shared->nsatiated = 0;
	pthread_mutex_init(&(shared->done_mutex), NULL);
	pthread_mutex_init(&(shared->forks), NULL);
	shared->done = FALSE;
	return (0);
}

static void	ft_destroy_shared(t_shared *shared)
{
	pthread_mutex_destroy(&(shared->done_mutex));
	pthread_mutex_destroy(&(shared->forks));
}

static int	ft_malloc_error3(void *a, void *b, void *c)
{
	if (!a || !b || !c)
	{
		free(a);
		free(b);
		free(c);
		ft_puterr("Fatal Error: bad alloc\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_shared		shared;
	pthread_t		*threads;
	t_philo			*philos;
	t_xmutex		*forks;

	if (!(ac == 5 || ac == 6) || ft_init_shared(&shared, av) == -1)
	{
		ft_puterr("invalid arguments.\ncall with: ");
		ft_puterr("philosophers num_philo time_to_die eat sleep [num_meals]\n");
		return (1);
	}
	philos = malloc(sizeof(t_philo) * shared.nphilo);
	threads = malloc(sizeof(pthread_t) * shared.nphilo);
	forks = malloc(sizeof(t_xmutex) * shared.nphilo);
	if (ft_malloc_error3(philos, threads, forks))
		return (1);
	ft_timestamp(TS_RESET);
	ft_launch_threads(&shared, threads, philos, forks);
	while (!shared.done)
		usleep(1000);
	ft_collect_threads(&shared, threads, philos, forks);
	ft_destroy_shared(&shared);
	return (0);
}

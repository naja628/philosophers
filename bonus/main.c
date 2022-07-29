/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:47 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:24:39 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <semaphore.h> 
#include <stdlib.h>
#include <signal.h>
#include "errcodes.h"
#include "satiation_thread.h"
#include "atoi_errcode.h"
#include "sems.h"
#include "timestamp.h"
#include "args.h"
#include "philo.h"

static int	ft_init_args(t_args *a, char **av)
{
	int	errcode;

	errcode = FUN_NO_ERROR;
	a->nphilo = ft_positive_atoi_errcode(av[1], &errcode);
	a->time_to_die = ft_positive_atoi_errcode(av[2], &errcode);
	a->time_to_eat = ft_positive_atoi_errcode(av[3], &errcode);
	a->time_to_sleep = ft_positive_atoi_errcode(av[4], &errcode);
	if (av[5])
		a->n_meals = ft_positive_atoi_errcode(av[5], &errcode);
	else
		a->n_meals = -1;
	return (errcode);
}

static void	ft_puterr(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write (2, s, len);
}

static void	ft_subprocesses(t_args *a, t_sems *sems, pid_t *pids)
{
	int			iphilo;
	pid_t		parent;
	pthread_t	satiation;

	iphilo = 1;
	while (iphilo <= a->nphilo)
	{
		parent = fork();
		if (parent)
			pids[iphilo++ - 1] = parent;
		else
			ft_philo(iphilo, a, sems, pids);
	}
	if (a->n_meals == -1
		|| ft_sat_thread(a->nphilo, sems, &satiation) == FUN_NO_ERROR)
		sem_wait(sems->finished_sem);
	iphilo = 1;
	while (iphilo <= a->nphilo)
		kill(pids[iphilo++ - 1], SIGINT);
}

int	main(int ac, char **av)
{
	t_args		a;
	t_sems		sems;
	pid_t		*pids;

	if (!(ac == 5 || ac == 6) || ft_init_args(&a, av) == FUN_ERROR)
	{
		ft_puterr("Error: arg\n");
		ft_puterr("usage: ./philo n t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	ft_init_sems(&sems, a.nphilo);
	pids = malloc(a.nphilo * sizeof(pid_t));
	if (!pids)
		return (1);
	ft_timestamp(TS_RESET);
	ft_subprocesses(&a, &sems, pids);
	free(pids);
	ft_close_sems(&sems);
	return (0);
}

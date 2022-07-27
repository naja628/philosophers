/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:37 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:20:40 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "launch_threads.h"

void	ft_init_philo(t_philo *philo, int i, t_shared *shared, t_xmutex *forks)
{
	int	ifork;

	ifork = 0;
	while (ifork < shared->nphilo)
		ft_init_xmutex(forks + ifork++);
	philo->index = i + 1;
	philo->times_eaten = 0;
	philo->last_ate = ft_timestamp(0);
	philo->shared = shared;
	philo->lfork = forks + i;
	philo->rfork = forks + ((i + 1) % shared->nphilo);
}

// s = shared, f = forks, t = threads, p = philos
void	ft_launch_threads(t_shared *s, pthread_t *t, t_philo *p, t_xmutex *f)
{
	int	i;

	i = 0;
	if (s->nphilo % 2 == 1)
	{
		while (i < s->nphilo)
		{
			ft_init_philo(p + i, i, s, f);
			pthread_create(t + i, NULL, ft_philo_odd, p + i);
			++i;
		}
	}
	else
	{
		while (i < s->nphilo)
		{
			ft_init_philo(p + i, i, s, f);
			pthread_create(t + i, NULL, ft_philo_even, p + i);
			++i;
		}
	}
}

void	ft_collect_threads(t_shared *s, pthread_t *t, t_philo *p, t_xmutex *f)
{
	int	i;

	i = 0;
	while (i < s->nphilo)
		pthread_join(t[i++], NULL);
	free(p);
	free(t);
	free(f);
}

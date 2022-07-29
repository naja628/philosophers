/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:48 by najacque          #+#    #+#             */
/*   Updated: 2022/07/20 15:41:58 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_utils.h"

// void	*ft_philo_routine(void *arg)
// {
// 	t_philo		*philo;
// 	t_shared	*shared;
// 	int			stagger;
// 	int			turn_dur;
// 
// 	philo = (t_philo *) arg;
// 	shared = ((t_philo *) arg)->shared;
// 	stagger = 1 + shared->nphilo / 25;
// 	turn_dur = (shared->nphilo % 2) * 3 * shared->time_to_eat + stagger;
// 	if (philo->index % 2 == 0)
// 		ft_think(shared, philo, stagger);
// 	else if (shared->nphilo % 2 == 1 && philo->index == 1)
// 		ft_think(shared, philo, 2 * shared->time_to_eat);
// 	else
// 		ft_think(shared, philo, 0);
// 	ft_eat(shared, philo);
// 	ft_sleep(shared, philo);
// 	while (!(shared->done))
// 	{
// 		ft_think(shared, philo, philo->last_ate + turn_dur - ft_timestamp(0));
// 		ft_eat(shared, philo);
// 		ft_sleep(shared, philo);
// 	}
// 	return (NULL);
// }

void	*ft_philo_even(void *arg)
{
	t_philo		*philo;
	t_shared	*shared;
	int			stagger;

	philo = (t_philo *) arg;
	shared = ((t_philo *) arg)->shared;
	stagger = 1 + shared->nphilo / 25;
	if (philo->index % 2 == 0)
		ft_think(shared, philo, stagger);
	else
		ft_think(shared, philo, 0);
	ft_eat_and_sleep(shared, philo);
	while (!(shared->done))
	{
		ft_think(shared, philo, 0);
		ft_eat_and_sleep(shared, philo);
	}
	return (NULL);
}

static void	ft_first_time_odd(t_philo *philo, t_shared *shared, int stagger)
{
	if (philo->index == 1)
		ft_think(shared, philo, (3 * shared->time_to_eat) / 2);
	else if (philo->index % 2 == 1)
		ft_think(shared, philo, stagger);
	else
		ft_think(shared, philo, 0);
	ft_eat_and_sleep(shared, philo);
}

void	*ft_philo_odd(void *arg)
{
	t_philo		*philo;
	t_shared	*shared;
	int			stagger;
	int			delay;
	int			k;

	philo = (t_philo *) arg;
	shared = ((t_philo *) arg)->shared;
	stagger = 1 + shared->nphilo / 25;
	delay = (5 * shared->time_to_eat) / 2;
	k = shared->nphilo / 2;
	ft_first_time_odd(philo, shared, stagger);
	while (!(shared->done))
	{
		if (philo->index / 2 % k == philo->times_eaten % k)
			ft_think(shared, philo, philo->last_ate + delay - ft_timestamp(0));
		else
			ft_think(shared, philo, 0);
		ft_eat_and_sleep(shared, philo);
	}
	return (NULL);
}

void	ft_think(t_shared *shared, t_philo *philo, int stagger)
{
	const int	dt_us = 1000;

	ft_status(shared, philo, "is thinking");
	if (stagger > 0)
		ft_philo_wait(shared, philo, stagger);
	while (!shared->done
		&& !ft_try_lock2(philo->lfork, philo->rfork, &(shared->forks)))
	{
		ft_maybe_die(shared, philo);
		usleep(dt_us);
	}
	ft_status(shared, philo, "has taken a fork");
	ft_status(shared, philo, "has taken a fork");
}

void	ft_eat_and_sleep(t_shared *shared, t_philo *philo)
{
	ft_status(shared, philo, "is eating");
	philo->last_ate = ft_timestamp(0);
	ft_philo_wait(shared, philo, shared->time_to_eat);
	ft_times_eaten(shared, philo);
	ft_unlock_xmutex(philo->lfork);
	ft_unlock_xmutex(philo->rfork);
	ft_status(shared, philo, "is sleeping");
	ft_philo_wait(shared, philo, shared->time_to_sleep);
}

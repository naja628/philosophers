/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:48 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:20:48 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_utils.h"

void	*ft_philo_routine(void *arg)
{
	t_philo		*philo;
	t_shared	*shared;
	int			stagger;

	philo = (t_philo *) arg;
	shared = ((t_philo *) arg)->shared;
	stagger = 1 + shared->nphilo / 25;
	if (philo->index % 2 == 0)
	{
		ft_think(shared, philo, stagger);
		ft_eat(shared, philo);
		ft_sleep(shared, philo);
	}
	while (!(shared->done))
	{
		ft_think(shared, philo, 0);
		ft_eat(shared, philo);
		ft_sleep(shared, philo);
	}
	return (NULL);
}

void	ft_think(t_shared *shared, t_philo *philo, int stagger)
{
	const int	dt_us = 1000;

	ft_status(shared, philo, "is thinking");
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

void	ft_eat(t_shared *shared, t_philo *philo)
{
	ft_status(shared, philo, "is eating");
	philo->last_ate = ft_timestamp(0);
	ft_philo_wait(shared, philo, shared->time_to_eat);
	ft_times_eaten(shared, philo);
	ft_unlock_xmutex(philo->lfork);
	ft_unlock_xmutex(philo->rfork);
}

void	ft_sleep(t_shared *shared, t_philo *philo)
{
	ft_status(shared, philo, "is sleeping");
	ft_philo_wait(shared, philo, shared->time_to_sleep);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:49 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:20:49 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void	ft_status(t_shared *shared, t_philo *philo, char const *msg)
{
	pthread_mutex_lock(&(shared->done_mutex));
	if (!shared->done)
		printf("%d %d %s\n", ft_timestamp(0), philo->index, msg);
	pthread_mutex_unlock(&(shared->done_mutex));
}

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// dt_ms should the how long it is acceptable to wait
// for the program to terminate after the simulation is done
// (bc a philo died or we ate enough times)
void	ft_philo_wait(t_shared *shared, t_philo *philo, unsigned int dur_ms)
{
	const int		dt_ms = 20;
	unsigned int	start;
	unsigned int	now;
	unsigned int	wait_dur;

	start = ft_timestamp(0);
	now = start;
	while (now < start + dur_ms)
	{
		if (shared->done || ft_maybe_die(shared, philo))
			return ;
		wait_dur = ft_min(dt_ms, philo->last_ate + shared->time_to_die - now);
		wait_dur = ft_min(wait_dur, start + dur_ms - now);
		usleep(1000 * wait_dur);
		now = ft_timestamp(0);
	}
}

void	ft_times_eaten(t_shared *shared, t_philo *philo)
{
	philo->times_eaten++;
	if (philo->times_eaten == shared->nmeals)
	{
		pthread_mutex_lock(&(shared->done_mutex));
		shared->nsatiated++;
		pthread_mutex_unlock(&(shared->done_mutex));
	}
	if (shared->nsatiated == shared->nphilo)
	{
		pthread_mutex_lock(&(shared->done_mutex));
		shared->done = TRUE;
		pthread_mutex_unlock(&(shared->done_mutex));
	}
}

int	ft_maybe_die(t_shared *shared, t_philo *philo)
{
	unsigned int	now;

	now = ft_timestamp(0);
	if (now > philo->last_ate + shared->time_to_die)
	{
		if (!(shared->done))
		{
			pthread_mutex_lock(&(shared->done_mutex));
			shared->done = TRUE;
			printf("%d %d %s\n", ft_timestamp(0), philo->index, "died");
			pthread_mutex_unlock(&(shared->done_mutex));
		}
		return (1);
	}
	return (0);
}

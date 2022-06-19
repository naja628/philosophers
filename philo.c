#include "philo.h"
#include "philo_utils.h"

void	*ft_philo_routine(void *arg)
{
	t_philo		*philo;
	t_shared	*shared;

	philo = (t_philo *) arg;
	shared = ((t_philo *) arg)->shared;
	// stagger based on parity?
	while (!(shared->done))
	{
		ft_think(shared, philo);
		ft_eat(shared, philo);
		ft_sleep(shared, philo);
	}
	return (NULL);
}

void	ft_think(t_shared *shared, t_philo *philo)
{
	const int	dt_us = 500;

	ft_status(shared, philo, "is thinking");
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

#include "philo.h"

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
	ft_status(shared, philo, "is thinking");
	ft_lock2(philo->left_fork, philo->right_fork, &(shared->fork_access));
	if (shared->done)
	{
		ft_unlock_xmutex(philo->left_fork);
		ft_unlock_xmutex(philo->right_fork);
		return ;
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
	ft_unlock_xmutex(philo->left_fork);
	ft_unlock_xmutex(philo->right_fork);
}

void	ft_sleep(t_shared *shared, t_philo *philo)
{
	ft_status(shared, philo, "is sleeping");
	ft_philo_wait(shared, philo, shared->time_to_sleep);
}

void	ft_status(t_shared *shared, t_philo *philo, char const *msg)
{
	pthread_mutex_lock(&(shared->done_mutex));
	if (!shared->done)
		printf("%d %d %s\n", ft_timestamp(0), philo->index, msg);
	pthread_mutex_unlock(&(shared->done_mutex));
}

void	ft_philo_wait(t_shared *shared, t_philo *philo, unsigned int dur_ms)
{
	const int		dt = 500;
	unsigned int	start;
	unsigned int	now;

	start = ft_timestamp(FALSE);
	now = start;
	while (now < start + dur_ms)
	{
		if (now > philo->last_ate + shared->time_to_die)
		{
			if (!(shared->done))
			{
				pthread_mutex_lock(&(shared->done_mutex));
				shared->done = TRUE;
				printf("%d %d %s\n", ft_timestamp(0), philo->index, "died");
				pthread_mutex_unlock(&(shared->done_mutex));
			}
			return ;
		}
		usleep(dt);
		now = ft_timestamp(0);
	}
}

void	ft_times_eaten(t_shared *shared, t_philo *philo)
{
	philo->times_eaten++;
	if (philo->times_eaten == shared->nmeals)
		shared->nsatiated++;
	if (shared->nsatiated == shared->nphilo)
	{
		pthread_mutex_lock(&(shared->done_mutex));
		shared->done = TRUE;
		pthread_mutex_unlock(&(shared->done_mutex));
	}
}

#include "philo_utils.h"

void	ft_status(t_shared *shared, t_philo *philo, char const *msg)
{
	pthread_mutex_lock(&(shared->done_mutex));
	if (!shared->done)
		printf("%d %d %s\n", ft_timestamp(0), philo->index, msg);
	pthread_mutex_unlock(&(shared->done_mutex));
}

void	ft_philo_wait(t_shared *shared, t_philo *philo, unsigned int dur_ms)
{
	const int		dt = 1000;
	unsigned int	start;
	unsigned int	now;

	start = ft_timestamp(0);
	now = start;
	while (now < start + dur_ms)
	{
		if (shared->done || ft_maybe_die(shared, philo))
			return ;
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

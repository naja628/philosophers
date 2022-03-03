#include <time.h>
#include <stdio.h>
#include "time_ops.h"
#include "philo.h"

// smallest time unit waited (in us)
#define TIME_ATOM 500

typedef struct	s_philo_data
{
	struct timeval	*last_ate;
	int				id;
	int				nmeals;
	char			finished;
	t_shared		*shared;
}	t_philo_data;

/* sensible mod */
static int	rem(int x, int d)
{
	if (x < 0)
		return (x % d + d);
	return (x % d);
}

static void	ft_init_philo(t_philo_data *data, void *arg)
{
	data->shared = ((t_data_wrap *) arg)->shared;
	data->id = ((t_data_wrap *) arg)->id;
	data->nmeals = 0;
	gettimeofday(data->last_ate, NULL);
	data->finished = 0;
	free(arg);
}

static void	ft_mortal_wait(t_shared *shared, t_philo_data *data, int dur_ms)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = ft_tv_diff_ms(&now, data->last_ate);
	while (diff <= dur_ms)
	{
		if (diff > shared->timetodie)
		{
			printf("%d %d is dead", ft_timestamp(0), data->id + 1); 
			shared->first_blood = 1;
		}
		if (shared->first_blood || diff > shared->timetodie)
		{
			data->finished = 1;
			break;
		}
		// TODO deal with nmeals thingy
		usleep(TIME_ATOM);
		gettimeofday(&now, NULL);
		diff = ft_tv_diff_ms(&now, data->last_ate);
	}
}
	
static void	ft_think(t_shared *shared, t_philo_data *data)
{
	printf("%d %d is thinking", ft_timestamp(0), data->id + 1); 
	while (!data->finished)
	{
		pthread_mutex_lock(shared->fork_access);
		if (shared->forks[rem(data->id, shared->nphilo)]
				|| shared->forks[rem(data->id + 1, shared->nphilo)])
		{
			shared->forks[rem(data->id, shared->nphilo)] = 0;
			printf("%d %d has taken a fork", ft_timestamp(0), data->id + 1); 
			shared->forks[rem(data->id + 1, shared->nphilo)] = 0;
			printf("%d %d has taken a fork", ft_timestamp(0), data->id + 1); 
			break;
		}
		pthread_mutex_unlock(shared->fork_access);
		ft_mortal_wait(shared, data, 1);
	}
	pthread_mutex_unlock(shared->fork_access);
}

static void	ft_eat_then_sleep(t_shared *shared, t_philo_data *data)
{
	gettimeofday(data->last_ate, NULL);
	printf("%d %d is eating", ft_timestamp(0), data->id + 1); 
	++(data->nmeals);
	ft_mortal_wait(shared, data, shared->timetoeat);
	pthread_mutex_lock(shared->fork_access);
	shared->forks[rem(data->id, shared->nphilo)] = 1;
	shared->forks[rem(data->id + 1, shared->nphilo)] = 1;
	pthread_mutex_unlock(shared->fork_access);
	if (data->finished)
		return ;
	printf("%d %d is sleeping", ft_timestamp(0), data->id + 1); 
	ft_mortal_wait(shared, data, shared->timetosleep);
}

void	*ft_philo(void *arg)
{
	t_philo_data	data;

	ft_init_philo(&data, arg);
	while (!data->finished)
	{
		ft_think(data->shared, data);
		ft_eat_then_sleep(data->shared, data);
	}
	return (NULL);
}

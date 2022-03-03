#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "time_ops.h"
#include "philo.h"

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
	gettimeofday(&(data->last_ate), NULL);
	data->finished = 0;
	free(arg);
}

/* wait dur_ms milliseconds but interrupt wait if the philo dies or the 
 * simulation must end */
static void	ft_mortal_wait(t_shared *shared, t_philo_data *data, int dur_ms)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = ft_tv_diff_ms(&now, &(data->last_ate));
	while (diff <= dur_ms)
	{
		if (diff > shared->timetodie)
		{
			printf("%d %d is dead\n", ft_timestamp(0), data->id + 1); 
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
		diff = ft_tv_diff_ms(&now, &(data->last_ate));
	}
}

static void	ft_think(t_shared *shared, t_philo_data *data)
{
	printf("%d %d is thinking\n", ft_timestamp(0), data->id + 1); 
	while (!data->finished)
	{
//		printf("1\n");
		pthread_mutex_lock(shared->fork_access);
//		printf("1.5\n");
//		printf("id is %d,", data->id);
//		printf("lr forks are %d %d\n", rem(data->id, shared->nphilo), rem(data->id + 1, shared->nphilo));
		if (shared->forks[rem(data->id, shared->nphilo)]
				&& shared->forks[rem(data->id + 1, shared->nphilo)])
		{
//			printf("2\n");
			shared->forks[rem(data->id, shared->nphilo)] = 0;
			printf("%d %d has taken a fork\n", ft_timestamp(0), data->id + 1); 
			shared->forks[rem(data->id + 1, shared->nphilo)] = 0;
			printf("%d %d has taken a fork\n", ft_timestamp(0), data->id + 1); 
//			printf("3\n");
			break;
		}
//		printf("4\n");
		pthread_mutex_unlock(shared->fork_access);
		ft_mortal_wait(shared, data, 1);
	}
	pthread_mutex_unlock(shared->fork_access);
}

static void	ft_eat_then_sleep(t_shared *shared, t_philo_data *data)
{
	gettimeofday(&(data->last_ate), NULL);
	printf("%d %d is eating\n", ft_timestamp(0), data->id + 1); 
	++(data->nmeals);
	ft_mortal_wait(shared, data, shared->timetoeat);
	pthread_mutex_lock(shared->fork_access);
	shared->forks[rem(data->id, shared->nphilo)] = 1;
	shared->forks[rem(data->id + 1, shared->nphilo)] = 1;
	pthread_mutex_unlock(shared->fork_access);
	if (data->finished)
		return ;
	printf("%d %d is sleeping\n", ft_timestamp(0), data->id + 1); 
	ft_mortal_wait(shared, data, shared->timetosleep);
}

/* philo thread, routine to be passed to 'pthread_create' */
void	*ft_philo(void *arg)
{
	t_philo_data	data;

	ft_init_philo(&data, arg);
//	printf("%d init ok\n", data.id + 1);
	while (!data.finished)
	{
		ft_think(data.shared, &data);
		ft_eat_then_sleep(data.shared, &data);
	}
	return (NULL);
}

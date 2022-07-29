#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "timestamp.h"
#include "killer_thread.h"
#include "philo.h"

static void	ft_status(int i, char const *msg, sem_t *guard)
{
	sem_wait(guard);
	printf("%d %d %s\n", ft_timestamp(0), i, msg);
	sem_post(guard);
}

// have a thread watching for when we need to close the semaphores
// (with free_sem added)
// delay sigterms so that things have time to be freed
void	ft_philo(int iphilo, t_args *a, t_sems *sems, void *freeme)
{
	int			last_ate;
	pthread_t	killer_thread;
	t_kt_data	data;

	free(freeme);
	ft_timestamp(TS_RESET);
	last_ate = ft_timestamp(0);
	data.iphilo = iphilo;
	data.last_ate = &last_ate;
	data.sems = sems;
	data.time_to_die = a->time_to_die;
	pthread_create(&killer_thread, NULL, ft_killer_thread, &data);
	pthread_detach(killer_thread);
	ft_philo_routine(iphilo, a, sems, &last_ate);
}

static void	ft_take2forks(int iphilo, t_sems *sems)
{
	sem_wait(sems->fork_taking);
	sem_wait(sems->forks_sem);
	ft_status(iphilo, "has taken a fork", sems->guard_sem);
	sem_wait(sems->forks_sem);
	ft_status(iphilo, "has taken a fork", sems->guard_sem);
	sem_post(sems->fork_taking);
}

void	ft_philo_routine(int iphilo, t_args *a, t_sems *sems, int *last_ate)
{
	int	times_eaten;

	times_eaten = 0;
	while (1)
	{
		ft_status(iphilo, "is thinking", sems->guard_sem);
		ft_take2forks(iphilo, sems);
		ft_status(iphilo, "is eating", sems->guard_sem);
		*last_ate = ft_timestamp(0);
		usleep(1000 * a->time_to_eat);
		sem_post(sems->forks_sem);
		sem_post(sems->forks_sem);
		if (++times_eaten == a->n_meals)
			sem_post(sems->nsatiated_sem);
		ft_status(iphilo, "is sleeping", sems->guard_sem);
		usleep(1000 * a->time_to_sleep);
	}
}

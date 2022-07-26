#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "timestamp.h"
#include "killer_thread.h"
#include "philo.h"

static void	ft_status(int i, char const * msg, sem_t *guard)
{
	sem_wait(guard);
	printf("%d %d %s\n", ft_timestamp(0), i, msg);
	sem_post(guard);
}

// static void ft_wait_or_die(int i, int dur_ms, int last_ate, t_args *a, t_sems *sems)
// {
// 	const int	dt = 1000;
// 	int			now;
// 	int			start;
// 	
// 	start = now = ft_timestamp(0);
// 	printf("philo %d waits. now : %d, last ate: %d\n", i, now, last_ate);
// 	while (now < start + dur_ms)
// 	{
// 		if (now - last_ate > a->time_to_die)
// 		{
// 			ft_status(i, "died", sems->guard_sem); // pb : between here and next line
// 			sem_wait(sems->guard_sem); // prevent all non-trivial operations
// 			sem_post(sems->finished_sem); // simulation done
// 		}
// 		usleep(dt);
// 		now = ft_timestamp(0);
// 	}
// }

// maybe TODO pass 'pids' and free it, 
// have a thread watching for when we need to close the semaphores
// (with free_sem added)
// delay sigterms so that things have time to be freed
void ft_philo(int iphilo, t_args *a, t_sems *sems, void *freeme)
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

void ft_philo_routine(int iphilo, t_args *a, t_sems *sems, int *last_ate)
{
	int times_eaten;
	times_eaten = 0;
	while(1)
	{
		// think
		ft_status(iphilo, "is thinking", sems->guard_sem);
		sem_wait(sems->forks_sem);
		ft_status(iphilo, "has taken a fork", sems->guard_sem);
		ft_status(iphilo, "has taken a fork", sems->guard_sem);
		// eat
		ft_status(iphilo, "is eating", sems->guard_sem);
		*last_ate = ft_timestamp(0);
// 		printf("%d last ate: %d\n", iphilo, last_ate);
		usleep(1000 * a->time_to_eat);
		sem_post(sems->forks_sem);
		if (++times_eaten == a->n_meals)
			sem_post(sems->nsatiated_sem);
		// sleep
		ft_status(iphilo, "is sleeping", sems->guard_sem);
		usleep(1000 * a->time_to_sleep);
	}
}

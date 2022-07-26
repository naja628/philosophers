#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include "sems.h"
#include "satiation_thread.h"
#include "errcodes.h"

#include <stdio.h>
void	*ft_satiation_thread(void *data)
{
	int		i;
	t_st_arg *a;

	a = (t_st_arg *) data;
	i = 0;
	while (i < a->nphilo)
	{
		sem_wait(a->sems->nsatiated_sem);
		++i;
	}
	sem_wait(a->sems->guard_sem);
	sem_post(a->sems->finished_sem);
	free(data);
	printf("pre-return \n");
	return (NULL);
}

int ft_sat_thread(int nphilo, t_sems *sems, pthread_t *thread_buf)
{
	t_st_arg *a;
	a = malloc(sizeof(t_st_arg));
	if (!a)
		return (FUN_ERROR);// problem
	a->sems = sems;
	a->nphilo = nphilo;
	pthread_create(thread_buf, NULL, ft_satiation_thread, a);
	printf("detaching. %d\n", pthread_detach(*thread_buf));
	return (FUN_NO_ERROR);
}

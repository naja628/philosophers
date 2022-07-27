#include <semaphore.h>
#include <fcntl.h>
#include "sems.h"

#define FORKS_NAME "forks"
#define FINISHED_NAME "finished"
#define NSATIATED_NAME "nsatiated"
#define GUARD_NAME "guard"

void	ft_init_sems(t_sems *sems, int nphilo)
{
	sem_unlink(FORKS_NAME);
	sems->forks_sem = sem_open(FORKS_NAME, O_CREAT, 0660, nphilo / 2);
	sem_unlink(FINISHED_NAME);
	sems->finished_sem = sem_open(FINISHED_NAME, O_CREAT, 0660, 0);
	sem_unlink(NSATIATED_NAME);
	sems->nsatiated_sem = sem_open(NSATIATED_NAME, O_CREAT, 0660, 0);
	sem_unlink(GUARD_NAME);
	sems->guard_sem = sem_open(GUARD_NAME, O_CREAT, 0660, 1);
}

void	ft_close_sems(t_sems *sems)
{
	sem_close(sems->forks_sem);
	sem_close(sems->finished_sem);
	sem_close(sems->nsatiated_sem);
	sem_close(sems->guard_sem);
	sem_unlink(FORKS_NAME);
	sem_unlink(FINISHED_NAME);
	sem_unlink(NSATIATED_NAME);
	sem_unlink(GUARD_NAME);
}

#undef FORKS_NAME
#undef FINISHED_NAME
#undef NSATIATED_NAME
#undef GUARD_NAME
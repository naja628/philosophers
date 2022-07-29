#ifndef SEMS_H
# define SEMS_H

# include <semaphore.h>

typedef struct s_sems
{
	sem_t	*forks_sem;
	sem_t	*finished_sem;
	sem_t	*nsatiated_sem;
	sem_t	*guard_sem;
	sem_t	*fork_taking;
}	t_sems;

void	ft_init_sems(t_sems *sems, int n);
void	ft_close_sems(t_sems *sems);

#endif

#ifndef SATIATION_THREAD_H
# define SATIATION_THREAD_H

# include "sems.h"

typedef struct s_st_arg
{
	int nphilo;
	t_sems * sems;
}	t_st_arg;

void	*ft_satiation_thread(void *data);
int ft_sat_thread(int nphilo, t_sems *sems, pthread_t *thread_buf);

#endif

#ifndef KILLER_THREAD_H
# define KILLER_THREAD_H

#include "sems.h"

typedef struct s_kt_data
{
	int	iphilo;
	int *last_ate; // must be changeable from outside
	t_sems *sems;
	int time_to_die;
}	t_kt_data;

void *ft_killer_thread(void *arg);
void ft_launch_killer_thread(int i, int *last_ate, t_sems *sems, int t_die);

#endif

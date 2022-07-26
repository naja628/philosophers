#ifndef PHILO_H
# define PHILO_H

# include "sems.h"
# include "args.h"

void ft_philo(int iphilo, t_args * a, t_sems *sems, void *freeme);
void ft_philo_routine(int iphilo, t_args *a, t_sems *sems, int *last_ate);

#endif

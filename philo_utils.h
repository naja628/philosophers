#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include "philo.h"

void	ft_status(t_shared *shared, t_philo *philo, char const *msg);
void	ft_philo_wait(t_shared *shared, t_philo *philo, unsigned int dur_ms);
void	ft_times_eaten(t_shared *shared, t_philo *philo);
int		ft_maybe_die(t_shared *shared, t_philo *philo);

#endif

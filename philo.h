#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "xmutex.h"
# include "timestamp.h"

typedef struct s_shared
{
	t_bool			done;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	int				nmeals;
	int				nphilo;
	int				nsatiated;
	pthread_mutex_t	done_mutex;
	pthread_mutex_t	fork_access;
}	t_shared;

typedef struct	s_philo
{
	int				index;
	int				times_eaten;
	unsigned int	last_ate;
	t_shared		*shared;
	t_xmutex		*left_fork;
	t_xmutex		*right_fork;
}	t_philo;

void	*ft_philo_routine(void *arg);
void	ft_think(t_shared *shared, t_philo *philo);
void	ft_eat(t_shared *shared, t_philo *philo);
void	ft_sleep(t_shared *shared, t_philo *philo);
void	ft_status(t_shared *shared, t_philo *philo, char const *msg);
void	ft_philo_wait(t_shared *shared, t_philo *philo, unsigned int dur_ms);
void	ft_times_eaten(t_shared *shared, t_philo *philo);

#endif

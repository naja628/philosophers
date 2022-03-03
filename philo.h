#ifndef PHILO_H
# define PHILO_H

// smallest time unit waited (in us)
# define TIME_ATOM 500

/* type meant to contain the ressources shared by all threads
 * ie, the shared field should point to the same object for all threads */
typedef struct s_shared
{
	char			first_blood;
	int				nphilo;
	int				timetoeat;
	int				timetosleep;
	int				timetodie;
	int				nmeals;
	char			*forks;
	pthread_mutex_t	*fork_access;
}	t_shared;

/* data each philo (ie thread) needs access to */
typedef struct	s_philo_data
{
	struct timeval	last_ate;
	int				id;
	int				nmeals;
	char			finished;
	t_shared		*shared;
}	t_philo_data;

/* (void *) wrapper used to pass the right info to 'pthread_create' */
typedef struct	s_data_wrap
{
	int 		id;
	t_shared	*shared;
}	t_data_wrap;

void	*ft_philo(void *arg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:21:21 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:21:21 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_t	forks;
}	t_shared;

typedef struct s_philo
{
	int				index;
	int				times_eaten;
	unsigned int	last_ate;
	t_shared		*shared;
	t_xmutex		*lfork;
	t_xmutex		*rfork;
}	t_philo;

void	*ft_philo_routine(void *arg);
void	ft_think(t_shared *shared, t_philo *philo, int stagger);
void	ft_eat(t_shared *shared, t_philo *philo);
void	ft_sleep(t_shared *shared, t_philo *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:21:20 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:21:20 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCH_THREADS_H
# define LAUNCH_THREADS_H

# include <pthread.h>
# include "philo.h"
# include "xmutex.h"

void	ft_init_philo(t_philo *philo, int i, t_shared *shared, t_xmutex *forks);
void	ft_launch_threads(t_shared *s, pthread_t *t, t_philo *p, t_xmutex *f);
void	ft_collect_threads(t_shared *s, pthread_t *t, t_philo *p, t_xmutex *f);

#endif

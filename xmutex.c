/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmutex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:20:52 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:20:52 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmutex.h"

//void	ft_lock2(t_xmutex *a, t_xmutex *b, pthread_mutex_t *access)
//{
//	const int	dt = 500;
//	t_bool		lock_success;
//
//	lock_success = FALSE;
//	while (!lock_success)
//	{
//		pthread_mutex_lock(access);
//		if (!a->locked && !b->locked)
//		{
//			ft_lock_xmutex(a);
//			ft_lock_xmutex(b);
//			lock_success = TRUE;
//		}
//		pthread_mutex_unlock(access);
//		usleep(dt);
//	}
//}

t_bool	ft_try_lock2(t_xmutex *a, t_xmutex *b, pthread_mutex_t *access)
{
	t_bool		lock_success;

	lock_success = FALSE;
	pthread_mutex_lock(access);
	if (!a->locked && !b->locked && &(a->mutex) != &(b->mutex))
	{
		ft_lock_xmutex(a);
		ft_lock_xmutex(b);
		lock_success = TRUE;
	}
	pthread_mutex_unlock(access);
	return (lock_success);
}

void	ft_init_xmutex(t_xmutex *m)
{
	m->locked = FALSE;
	pthread_mutex_init(&(m->mutex), NULL);
}

void	ft_destroy_xmutex(t_xmutex *m)
{
	pthread_mutex_destroy(&(m->mutex));
}

#include <stdio.h>
void	ft_lock_xmutex(t_xmutex *m)
{
	pthread_mutex_lock(&(m->mutex));
	m->locked = TRUE;
}

void	ft_unlock_xmutex(t_xmutex *m)
{
	pthread_mutex_unlock(&(m->mutex));
	m->locked = FALSE;
}

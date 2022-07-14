/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmutex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:21:24 by najacque          #+#    #+#             */
/*   Updated: 2022/07/14 15:21:24 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMUTEX_H
# define XMUTEX_H

# include <pthread.h>
# include <unistd.h>

typedef char	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct s_xmutex
{
	t_bool			locked;
	pthread_mutex_t	mutex;
}	t_xmutex;

//void	ft_lock2(t_xmutex *a, t_xmutex *b, pthread_mutex_t *access);
t_bool	ft_try_lock2(t_xmutex *a, t_xmutex *b, pthread_mutex_t *access);
void	ft_init_xmutex(t_xmutex *m);
void	ft_destroy_xmutex(t_xmutex *m);
void	ft_lock_xmutex(t_xmutex *m);
void	ft_unlock_xmutex(t_xmutex *m);

#endif

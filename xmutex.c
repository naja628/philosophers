#include "xmutex.h"

void	ft_lock2(t_xmutex *a, t_xmutex *b, pthread_mutex_t *access)
{
	const int	dt = 500;
	t_bool		lock_success;

	lock_success = FALSE;
	while (!lock_success)
	{
		pthread_mutex_lock(access);
		if (!a->locked && !b->locked)
		{
			ft_lock_xmutex(a);
			ft_lock_xmutex(b);
			lock_success = TRUE;
		}
		pthread_mutex_unlock(access);
		usleep(dt);
	}
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

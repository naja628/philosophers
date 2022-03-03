#include <sys/time.h>
#include <stddef.h>
#include "time_ops.h"

/* compute diff between 2 'time.h' 'struct timeval's
 * as a number of milliseconds
 * hopefully overflow safe as long as the result is within an int
 */
int	ft_tv_diff_ms(struct timeval const *t, struct timeval const *u)
{
	int	ms;

	ms = 1000 * (t->tv_sec - u->tv_sec);
	ms += (int) (t->tv_usec / 1000) - (int) (u->tv_usec / 1000);
	return (ms);
}

int ft_timestamp(int start_now)
{
	static struct timeval	program_start;
	struct timeval			now;

	if (start_now)
	{
		gettimeofday(&program_start, NULL);
		return (0);
	}
	gettimeofday(&now, NULL);
	return (ft_tv_diff_ms(&now, &program_start));
}

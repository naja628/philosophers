#include "timestamp.h"

//// debug
//#include <stdio.h>

unsigned int	ft_timestamp(int reset)
{
	static struct timeval	start;
	struct timeval			now;
	unsigned int			diff_ms;

	if (reset == TS_RESET)
	{
		gettimeofday(&start, NULL);	
		return (0);
	}
	gettimeofday(&now, NULL);
	diff_ms = 1000 * (now.tv_sec - start.tv_sec);
//	printf("timestamp (no usec) %u\n", diff_ms);
	diff_ms += ((int) now.tv_usec - (int) start.tv_usec) / 1000;
//	printf("timestamp (with usec) %u\n", diff_ms);
	return (diff_ms);
}

#include "timestamp.h"

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
	diff_ms += ((int) now.tv_usec - (int) start.tv_usec) / 1000;
	return (diff_ms);
}

// #include <stdio.h>
// #include <unistd.h>
// int main()
// {
// 	int now = ft_timestamp(TS_RESET);
// 	int cnt = 0;
// 	// one
// 	while (now < 2000) // 2 sec
// 	{
// 		usleep(1);
// 		++cnt;
// 		now = ft_timestamp(0);
// 	}
// 	printf("count : %d\n", cnt);
// 	// two
// 	usleep(1000000);	
// 	printf("now: %d\n", ft_timestamp(0));
// 
// 
// 	return 0;
// }
// // TODO rm ^

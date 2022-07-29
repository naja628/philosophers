#include <pthread.h>
#include <unistd.h>

void *routine(void *a)
{
	(void) a;
	return NULL;
}

int main()
{
	pthread_t it;
	pthread_create(&it, NULL, routine, NULL);
	pthread_detach(it);
	sleep(1);
	return 0;
}


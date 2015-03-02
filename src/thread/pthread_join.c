#include "pthread_impl.h"
#include <sys/mman.h>

int __munmap(void *, size_t);

int __pthread_join(pthread_t t, void **res)
{
	int tmp;
	pthread_testcancel();
	while ((tmp = t->tid)) __timedwait_cp(&t->tid, tmp, 0, 0, 0);
	if (res) *res = t->result;
	if (t->map_base) __munmap(t->map_base, t->map_size);
	return 0;
}

weak_alias(__pthread_join, pthread_join);

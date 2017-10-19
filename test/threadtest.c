#include <stdio.h>
#include "thread/thread.h"

PRRET PRTHAPI subthread1(PRPARAM param)
{
	printf("thread1\n");
	return PRRETURN(param);
}

PRRET PRTHAPI subthread2(PRPARAM param)
{
	printf("thread2\n");
	return PRRETURN(param);
}

int main(int argc, char* argv[])
{
	int status;
	thread_t 	sub1_th;
	thread_t 	sub2_th;
	mutex_t 	sync_mutex;

	thread_create(sub1_th, subthread1, NULL);
	thread_create(sub2_th, subthread2, NULL);

	thread_termwait(sub1_th, status);
	thread_termwait(sub2_th, status);
	return 0;
}

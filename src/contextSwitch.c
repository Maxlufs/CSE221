#include <stdio.h>
// #include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cycle.h"

#define LOOP_COUNT 1000

int main(int argc, char *argv[])
{
	pid_t pid;
	int i;

	ticks t1 = getticks();
	for (i = 0; i < LOOP_COUNT; ++i) {
		if (fork() == 0) {
			_exit(0);
		}
	}
	ticks t2 = getticks();
	ticks d1 = t2 - t1;
	/*double d1 = elapsed(t2,t1);*/

	ticks t3 = getticks();
	for (i = 0; i < LOOP_COUNT; ++i) {
		if (( pid = fork() )== 0) {
			_exit(0);
		}
		waitpid(pid, NULL, 0);
	}
	//  Wait for any child; id is ignored.
	ticks t4 = getticks();
	ticks d2 = t4 - t3;
	/*double d2 = elapsed(t4,t3);*/

	printf("d1 = %d, d2 = %d, d2-d1 =%d\n ", (int)d1, (int)d2, (int)(d2-d1));
	printf("process context switch: %f\n", (double)(d2-d1) / 2 / LOOP_COUNT);

	return 0;
}

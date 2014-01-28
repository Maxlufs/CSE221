#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cycle.h"

#define LOOP_COUNT 100000

void contextSwitchOverhead() {
	ticks t1 = getticks();
	if (fork() == 0) {
		_exit(0);
	}
	ticks t2 = getticks();
	double d1 = elapsed(t2,t1);

	ticks t3 = getticks();
	if (fork() == 0) {
		_exit(0);
	}
	waitpid(P_ALL, NULL, 0);
	ticks t4 = getticks();
	double d2 = elapsed(t4,t3);

	printf("d1 = %f, d2 = %f\n", d1, d2);
}

int main(int argc, char *argv[])
{
	contextSwitchOverhead();
	return 0;
}

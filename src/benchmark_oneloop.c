#define LOOP_COUNT 10000000
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "cycle.h"

void __attribute__ ((noinline)) func_syscall(void) { getppid(); __asm__ __volatile__(""); }
void __attribute__ ((noinline)) func_donothing(void) { /*__asm__ __volatile__(""); */}


int main(int argc, char *argv[])
{

	float avg1 = 0.1, avg2 = 0.0, avg3 = 0.0, avg4 = 0.0, avg5 = 0.0;
	int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;
	ticks t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;
	int i;

	for (i = 0; i < LOOP_COUNT; ++i)
	{
		t1 = getticks();
		func_syscall();
		t2 = getticks();
		ticks d1 = t2 - t1;
		// printf("func call d1 = %llu\n", t2 - t1);
		// printf("func call d1 = %llu, d2 = %llu\n", d1, d2);
		sum1 += (int)d1;
		//sum2 += (int)d2;


		t3 = getticks();
		t4 = getticks();
		ticks d2 = t4 - t3;
		sum2 += (int)d2;


		t5 = getticks();
		getppid();
		t6 = getticks();
		ticks d3 = t6 - t5;
		// printf("func call d1 = %llu\n", t2 - t1);
		// printf("func call d1 = %llu, d2 = %llu\n", d1, d2);
		sum3 += (int)d3;


		t7 = getticks();
		t8 = getticks();
		// ticks d4 = t2 - t1;
		// // printf("func call d1 = %llu\n", t2 - t1);
		// // printf("func call d1 = %llu, d2 = %llu\n", d1, d2);
		// // sum4 += (int)d4;
		ticks d4 = t8 - t7;
		// printf("func call d1 = %llu\n", t2 - t1);
		// printf("func call d1 = %llu, d2 = %llu\n", d1, d2);
		sum4 += (int)d4;

		t9 = getticks();
		t10 = getticks();
		ticks d5 = t10 - t9;
		sum5 += (int)d5;

	}
	avg1 = sum1 / LOOP_COUNT;
	printf("avg noinline procedual call with system call = %f\n", avg1);
	avg2 = sum2 / LOOP_COUNT;
	printf("avg noinline procedual call = %f\n", avg2);
	avg3 = sum3 / LOOP_COUNT;
	printf("avg inline pure system call = %f\n", avg3);
	avg4 = sum4 / LOOP_COUNT;
	printf("avg inline pure ticks = %f\n", avg4);
	avg5 = sum5 / LOOP_COUNT;
	printf("avg inline pure ticks = %f\n", avg5);
	return 0;
}

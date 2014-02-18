#include <sys/types.h>
// for pid_t
#include <unistd.h>
// for pipe
#include <stdio.h>
#include <stdlib.h>
// forr EXIT_FAILURE

#include "cycle.h"

#define LOOP_COUNT 1000000

/*
 *void
 *read_from_pipe(int file) {
 *    FILE* stream;
 *
 *    int c; // character
 *
 *    stream = fdopen(file, "r");
 *    while (( c = fgetc (stream) ) != EOF)
 *        putchar(c);
 *    fclose (stream);
 *}
 *
 *void
 *write_to_pipe(int file) {
 *    FILE* stream;
 *    stream = fdopen(file, "w");
 *    fprintf(stream, "hello, world!\n");
 *    fprintf(stream, "goodbye, would!\n");
 *    fclose(stream);
 *}
 */

int main(int argc, char *argv[]) {
	pid_t pid;
	int fd[2]; // file descriptors for pipe

	char* a = (char*)malloc(sizeof(char));
	a[0] = 'a';
	/*char a = 'a';*/
	int sum = 0.0;
	double avg = 0.0;

	/*basic syntax:                                 */
	/*pipe(fd);                                     */
	/*return 0 success, -1 errno = [EMFILE | EFAULT]*/

	if (pipe(fd)) {
		fprintf(stderr, "Pipe failed.\n");
		return EXIT_FAILURE;
	}

	/*open a pipe to parent itself, test time*/
	int i;
	for (i = 0; i < LOOP_COUNT; ++i) {
		ticks t1 = getticks();
		write(fd[1],a,1);
		read(fd[0],a,1);
		ticks t2 = getticks();
		ticks d = t2 - t1;
		sum += (int)d;
	}

	avg = (double)sum / LOOP_COUNT;
	fprintf(stdout, "avg = %f\n", avg);

	free(a);

	/*cast 0 to pid_t*/
	/*if (( pid = fork() ) < (pid_t) 0) {*/
	/*fprintf(stderr, "Fork failed\n");*/
	/*return EXIT_FAILURE;*/
	/*}*/

	/*if (pid == (pid_t) 0) {  Child process*/
	/*close(fd[1]);  close write, try to read*/
	/*read_from_pipe(fd[0]);*/
	/*exit(0);*/
	/*}*/
	/*else {  parent process*/
	/*close(fd[0]);  close read, try to write*/
	/*write_to_pipe(fd[1]);*/
	/*exit(0);*/
	/*return EXIT_SUCCESS;*/
	/*use exit instead of return, so the child process terminates*/
	/*immediately */
	/*}*/

	return 0;
}

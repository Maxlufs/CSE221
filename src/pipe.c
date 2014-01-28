#include <sys/types.h>
// for pid_t
#include <unistd.h>
// for pipe
#include <stdio.h>
#include <stdlib.h>
// forr EXIT_FAILURE

#include "cycle.h"

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

	/*basic syntax:                                 */
	/*pipe(fd);                                     */
	/*return 0 success, -1 errno = [EMFILE | EFAULT]*/

	if (pipe(fd)) {
		fprintf(stderr, "Pipe failed.\n");
		return EXIT_FAILURE;
	}

	/*open a pipe to parent itself, test time*/
	ticks t1 = getticks();
	ticks t2 = getticks();

	/*cast 0 to pid_t*/
	if (( pid = fork() ) < (pid_t) 0) {
		fprintf(stderr, "Fork failed\n");
		return EXIT_FAILURE;
	}

	if (pid == (pid_t) 0) { // Child process
		close(fd[1]); // close write, try to read
		/*read_from_pipe(fd[0]);*/
		exit(0);
	}
	else { // parent process
		close(fd[0]); // close read, try to write
		/*write_to_pipe(fd[1]);*/
		exit(0);
		/*return EXIT_SUCCESS;
		 * use exit instead of return, so the child process terminates
		 * immediately */
	}

	return 0;
}

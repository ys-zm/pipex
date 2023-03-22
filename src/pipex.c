//TO RESEARCH
// pipe, fork, dup2, execve

#include <unistd.h>
//pid, when in the main process is not 0. when in the child process is 0.
//copies the main in another locatino in memory.
//wait() returns the process id of the thing you waited for
int	main(int argc, char **argv)
{
	int	pid;

	pid = fork();
	if (pid)
		//parent process
	else
		//child process. id = 0;
}

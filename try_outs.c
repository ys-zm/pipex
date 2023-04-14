//TO RESEARCH
// pipe, fork, dup2, execve

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

//pid, when in the main process is not 0. when in the child process is 0.
//copies the main in another locatino in memory.
//wait() returns the process id of the thing you waited for
int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	arr[8] = {1, 1, 1, 1, 2, 2, 2, 2};
	int	arrSize = sizeof(arr) / sizeof(int);
	int	total = 0;

	//fd[0] = read // fd[1] = write
	pipe(fd);
	pid1 = fork();
	if (pid1)
		pid2 = fork();

	if (pid1 == 0 || pid2 == 0)
	{
		int	start = 0;
		int	end = arrSize / 2;
		while (start < end)
			total += arr[start++];
		int	currPid = getpid();
		printf("total from pid %d is  %d\n", currPid, total);

	}
	else
	{
		int	start = arrSize / 2;
		int	end = arrSize;
		while (start < end)
			total += arr[start++];
		printf("total from parent is %d\n", total);
	}

	if (pid1 == 0)
	{
		close(fd[0]);
		write(fd[1], &total, sizeof(total));
		close(fd[1]);
	}
	if (pid1 && pid2)
	{
		int	totalFromChild;

		close(fd[1]);
		read(fd[0], &totalFromChild, sizeof(totalFromChild));
		close(fd[0]);
		printf("total from child: %d\n", totalFromChild);
		total += totalFromChild;
	}

	if (pid2 == 0)
	{
		close(fd[0]);
		write(fd[1], &total, sizeof(total));
		close(fd[1]);
	}
	if (pid1 && pid2)
	{
		int	totalFromChild;

		close(fd[1]);
		read(fd[0], &totalFromChild, sizeof(totalFromChild));
		close(fd[0]);
		
		printf("total from child2 is %d\n", totalFromChild);
		total += totalFromChild;
		printf("complete total is %d\n", total);
		wait(NULL);
	}
}
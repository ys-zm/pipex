#include "pipex.h"
#include <sys/wait.h>

//QUESTIONS
//whats the difference between _execve or execve();
void	make_pipes(int fd_in, int fd_out, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		ft_error_msg("Problem with creating pipes.", 1);
	pid1 = fork();
	if (pid1 < 0)
		ft_error_msg("Error with fork 1.", 1);
	else if (pid1 == 0)
		child_one(fd, fd_in, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		ft_error_msg("Error with fork 2.", 1);
	else if (pid2 == 0)
		child_two(fd, fd_out, argv, envp);
	close(fd[READ]);
	close(fd[WRITE]);
	waitpid(pid1, &status, NULL);
	wait(NULL);
	close(fd_in);
	close(fd_out);
}

int main(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	
	if (argc != 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		return (1);
	}

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		ft_error_msg("Infile does not exist.\n", 1);
	fd_out = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0664);
	make_pipes(fd_in, fd_out, argv, envp);
}
#include "pipex.h"

int	parent_process(int *fd, int fd_in, int fd_out, pid_t child1, pid_t child2)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	close(fd[READ]);
	close(fd[WRITE]);
	close(fd_in);
	close(fd_out);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	make_pipes(int fd_in, int fd_out, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		ft_error_msg("Problem with creating pipes.", 1);
	pid1 = fork();
	if (pid1 == -1)
		ft_error_msg("Error with fork 1.", 1);
	else if (pid1 == 0)
		child_one(fd, fd_in, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_error_msg("Error with fork 2.", 1);
	else if (pid2 == 0)
		child_two(fd, fd_out, argv, envp);
	status = parent_process(fd, fd_in, fd_out, pid1, pid2);
	return (status);
}

int main(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	int		status;
	int		i;

	i = 0;

	if (argc != 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		exit(EXIT_FAILURE);
	}

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (fd_in < 0)
		ft_error_msg("", 0);
	status = make_pipes(fd_in, fd_out, argv, envp);
	printf("status: %d\n", status);
	exit_pipes(status);
}
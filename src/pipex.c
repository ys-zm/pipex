/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/17 19:12:25 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_leaks(void)
{
	system("leaks -q pipex");
}

int	parent_process(int *fd, int *files, pid_t child1, pid_t child2)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	close(fd[READ]);
	close(fd[WRITE]);
	close(files[IN]);
	close(files[OUT]);
	waitpid(child1, NULL, 0);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	make_pipes(int *files, char **argv, char **envp)
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
		child_one(fd, files[IN], argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_error_msg("Error with fork 2.", 1);
	else if (pid2 == 0)
		child_two(fd, files[OUT], argv, envp);
	status = parent_process(fd, files, pid1, pid2);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int		files[2];
	int		status;
	int		i;

	i = 0;
	if (argc != 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	files[IN] = open(argv[1], O_RDONLY);
	files[OUT] = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (files[IN] < 0)
		ft_error_msg("", 0);
	status = make_pipes(files, argv, envp);
	exit_pipes(status);
	return (0);
}


// int main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;
// 	char *args[] = {
// 		" ",
// 		NULL
// 	};

// 	int ret = execve(NULL, args, envp);
// 	printf("ret %d\n", ret);
// 	return 0;
// }
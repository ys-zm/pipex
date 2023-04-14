/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:28:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/14 16:52:44 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exe_cmd(char **cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = check_access(cmd, envp);
	execve(cmd_path, cmd, envp);
	ft_error_msg(cmd_path, 127);
}

void	child_one(int *fd, int fd_in, char **argv, char **envp)
{
	char	**cmd_and_args;

	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd[WRITE], STDOUT_FILENO) == -1)
		ft_error_msg("Error with dup2 in Child One.\n", 1);
	if (close(fd[READ]) == -1 || close(fd_in) == -1)
		ft_error_msg("Error with closing unused fd's in Child One.\n", 1);
	cmd_and_args = separate_command_args(argv[2]);
	exe_cmd(cmd_and_args, envp);
}

void	child_two(int *fd, int fd_out, char **argv, char **envp)
{
	char	**cmd_and_args;

	if (dup2(fd[READ], STDIN_FILENO) == -1 || \
			dup2(fd_out, STDOUT_FILENO) == -1)
		ft_error_msg("Error with dup2 in Child Two.\n", 1);
	if (close(fd[WRITE]) == -1 || close(fd_out) == -1)
		ft_error_msg("Error with closing unused fd's in Child Two.\n", 1);
	cmd_and_args = separate_command_args(argv[3]);
	exe_cmd(cmd_and_args, envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/17 20:28:46 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    first_child(t_pipex *pipex, char **envp, char *file_in)
{
    pipex->fd_in = open(file_in, O_RDONLY);
    if (pipex->fd_in == -1)
        ft_error_msg("file_in", 1);
    dup2(pipex->fd_in, STDIN_FILENO);
    close(pipex->fd_in);
    dup2(pipex->pipes[0].fd[WRITE], STDOUT_FILENO);
    close_pipes(pipex);
    common_child_actions(pipex, envp, 0);
}

void    mid_child(t_pipex *pipex, char **envp, int pos)
{
  
    dup2(pipex->pipes[pos - 1].fd[READ], STDIN_FILENO);
    dup2(pipex->pipes[pos].fd[WRITE], STDOUT_FILENO);
    close_pipes(pipex);
    common_child_actions(pipex, envp, pos);
}

void    last_child(t_pipex *pipex, char **envp, int pos, char **argv)
{
    pipex->fd_out = open(argv[pipex->size + 2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    dup2(pipex->fd_out, STDOUT_FILENO);
    dup2(pipex->pipes[pos - 1].fd[READ], STDIN_FILENO);
    close(pipex->fd_out);
    close_pipes(pipex);
    common_child_actions(pipex, envp, pos);
}

void    common_child_actions(t_pipex *pipex, char **envp, int pos)
{
    char    *cmd_path;

    cmd_path = check_access(pipex, pos);
	execve(cmd_path, pipex->cmds[pos].args, envp);
    ft_error_msg(cmd_path, 127);
}
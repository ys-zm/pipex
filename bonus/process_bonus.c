/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/17 15:22:54 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    close_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->size - 1)
    {
        close(pipex->pipes[i].fd[READ]);
        close(pipex->pipes[i].fd[WRITE]);
        i++;
    }
}

void    wait_for_children(t_pipex *pipex)
{
    int i;
    int status;

    i = 0;
    while (i < pipex->size)
    {
        waitpid(pipex->pid[i], &status, 0);
        if (WIFEXITED(status))
            pipex->status = WEXITSTATUS(status);
        i++;
    }
}


void    process_management(t_pipex *pipex, char **envp, char **argv)
{
    int i;

    i = 0;
    pipex->pid[i] = fork();
    if (pipex->pid[i] == 0)
    {
        first_child(pipex, envp, argv[1]); 
    }  
    else
    {
    i++;
    while (i < pipex->size - 1)
    {
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
        {
            mid_child(pipex, envp, i);
        }
        i++;
    }
    } 
    if (i == pipex->size - 1)
    {
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
        {
            last_child(pipex, envp, i, argv);
        }
    }
    close(pipex->pipes[i - 1].fd[WRITE]);
}

void    parent_process(t_pipex *pipex, char **envp, char **argv)
{
    process_management(pipex, envp, argv);
    close(pipex->fd_in);
    close(pipex->fd_out);
    close_pipes(pipex);
    wait_for_children(pipex);
}
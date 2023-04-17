/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/17 21:04:14 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    ft_error_msg(const char *str, int error)
{
    perror(str);
    exit(error);
}

void    free_cmd_struct(t_pipex *pipex)
{   
    int i;
    int j;

    j = 0;
    i = 0;
    while (i < pipex->size)
    {
        while (pipex->cmds[i].args[j])
        {
            free(pipex->cmds[i].args[j]);
            j++;
        }
        i++;
    }
}

void    free_fd_struct(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->size - 1)
    {
        free(pipex->pipes[i].fd);
        i++;
    }
    
}

void    free_strings(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
}

void    ft_free_all(t_pipex *pipex)
{
    free_cmd_struct(pipex);
    free_fd_struct(pipex);
    free_strings(pipex->paths);
    free(pipex->pid);
}

void    exit_pipes(t_pipex *pipex)
{
    ft_free_all(pipex);
    exit(pipex->status);
}

void    print_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        write(STDERR_FILENO, array[i], ft_strlen(array[i]));
        write(STDERR_FILENO, "\n", 1);
        i++;
    }
}

void	malloc_protect(t_pipex *pipex, void	*var)
{
    ft_free_all(pipex);
	if (!var)
		ft_error_msg("", 1);
}
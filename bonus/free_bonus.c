/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 15:08:32 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_ints_arr(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

void	free_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd_struct(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size)
	{
		free_strings(pipex->cmds[i].args);
		i++;
	}
	free(pipex->cmds);
}

void	ft_free_all(t_pipex *pipex)
{
	free_cmd_struct(pipex);
	free_ints_arr(pipex);
	free_strings(pipex->paths);
	free(pipex->pid);
}

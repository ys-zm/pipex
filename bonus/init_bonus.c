/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:11:44 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 15:12:20 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_empty_str(char *str, t_pipex *pipex)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		malloc_protect(pipex, NULL);
	arr[0] = ft_strdup(str);
	if (!arr[0])
		malloc_protect(pipex, NULL);
	arr[1] = NULL;
	return (arr);
}

void	separate_cmd_arguments(t_pipex *pipex, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (i < pipex->size)
	{
		if (check_empty_str(argv[j]))
			pipex->cmds[i].args = ft_empty_str(argv[j], pipex);
		else
		{
			pipex->cmds[i].args = ft_split(argv[j], ' ');
			if (pipex->cmds[i].args == NULL)
				malloc_protect(pipex, NULL);
		}	
		i++;
		j++;
	}
}

void	set_up_struct(t_pipex *pipex)
{
	pipex->paths = NULL;
	pipex->cmds = NULL;
	pipex->fd_in = 0;
	pipex->fd_out = 0;
	pipex->pid = NULL;
	pipex->pipes = NULL;
	pipex->status = 0;
}

void	ft_init(t_pipex *pipex, char **argv)
{
	int	i;

	i = 0;
	pipex->pid = malloc(sizeof(pid_t) * pipex->size);
	pipex->pipes = malloc(sizeof(int *) * (pipex->size - 1));
	pipex->cmds = malloc(sizeof(t_cmd) * pipex->size);
	if (!pipex->pid || !pipex->pipes || !pipex->cmds)
		malloc_protect(pipex, NULL);
	separate_cmd_arguments(pipex, argv);
	while (i < pipex->size - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			malloc_protect(pipex, NULL);
		i++;
	}
}

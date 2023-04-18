/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 12:09:11 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_leaks(void)
{
	system("leaks -q pipex");
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size - 1)
	{
		if (pipe(pipex->pipes[i].fd) == -1)
		{
			//ft_free_all(pipex);
			ft_error_msg("Opening pipes failed.\n", 1);
		}
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	
	atexit(&ft_leaks);
	if (argc < 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		return (1);
	}
	pipex.size = argc - 3;
	path_parsing(&pipex, envp);
	ft_init(&pipex, argv);
	create_pipes(&pipex);
	parent_process(&pipex, envp, argv);
	exit_pipes(&pipex);
}
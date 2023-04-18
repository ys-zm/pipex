/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 15:21:57 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error_msg(const char *str, int error)
{
	perror(str);
	exit(error);
}

void	exit_pipes(t_pipex *pipex)
{
	ft_free_all(pipex);
	exit(pipex->status);
}

void	print_array(char **array)
{
	int	i;

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
	if (!var)
	{
		ft_free_all(pipex);
		ft_error_msg("", 1);
	}
}

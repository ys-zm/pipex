/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:32:26 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/14 16:52:48 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_msg(const char *str, int error)
{
	perror(str);
	exit(error);
}

void	exit_pipes(int status)
{
	exit(status);
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
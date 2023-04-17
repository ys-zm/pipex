/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:33:29 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/17 20:27:22 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path_var(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (envp[i]);
}

char	**path_parsing(char **envp)
{
	char	*path_temp;
	char	*path_env;
	char	**cmd_paths;

	path_temp = find_path_var(envp);
	if (path_temp)
	{
		path_env = ft_substr(path_temp, 5, ft_strlen(path_temp));
		cmd_paths = ft_split(path_env, ':');
		return (cmd_paths);
	}
	return (NULL);
}

bool	check_empty_str(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '\0')
		return (true);
	while (str && str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}

char	**separate_command_args(char *str)
{
	char	**cmd_and_args;

	cmd_and_args = NULL;
	if (!check_empty_str(str))
	{
		cmd_and_args = ft_split(str, ' ');
		if (cmd_and_args == NULL)
			malloc_protect(cmd_and_args);
	}
	return (cmd_and_args);
}

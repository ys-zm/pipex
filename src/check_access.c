/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_access.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:28:18 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 12:42:56 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_env_paths(char **env_path, char *cmd)
{
	char	*add_slash;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	while (env_path && env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		if (add_slash)
			cmd_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (cmd_path && !access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*check_current_directory(char *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin("./", cmd);
	if (cmd_path && !access(cmd_path, X_OK))
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*check_access(char **cmd_and_args, char **envp)
{
	char	**env_path;
	char	*cmd_path;

	cmd_path = NULL;
	env_path = path_parsing(envp);
	if (!access(cmd_and_args[0], X_OK))
		return (cmd_and_args[0]);
	else if (env_path)
	{
		cmd_path = check_env_paths(env_path, cmd_and_args[0]);
		if (cmd_path)
			return (cmd_path);
		free(cmd_path);
	}
	else
	{
		cmd_path = check_current_directory(cmd_and_args[0]);
		if (cmd_path)
			return (cmd_path);
	}
	free(env_path);
	return (NULL);
}

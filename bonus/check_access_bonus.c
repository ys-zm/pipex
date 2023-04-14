/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_access_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/14 17:24:27 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*check_env_paths(char **env_path, char *cmd)
{
	char	*add_slash;
	char	*cmd_path;
	int		i;

	i = 0;
	while (env_path && env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (!access(cmd_path, X_OK))
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
	if (!access(cmd_path, X_OK))
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*check_access(t_pipex *pipex, int pos)
{
	int		i;
	char	*cmd_path;
   
	i = 0;
    if (!access(pipex->cmds[pos].args[0], X_OK))
        return(pipex->cmds[pos].args[0]);
    else if (pipex->paths)
    {
        cmd_path = check_env_paths(pipex->paths, pipex->cmds[pos].args[0]);
        if (cmd_path)
            return (cmd_path);
        free(cmd_path);
    }
    else
    {
        cmd_path = check_current_directory(pipex->cmds[pos].args[0]);
        if (cmd_path)
            return (cmd_path);
    }
	return (NULL);
}
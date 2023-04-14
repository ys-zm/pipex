/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_parsing_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/14 16:35:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/14 16:58:30 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char    *find_path_var(char **envp)
{
    size_t i;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
        i++;
    if (!envp[i])
        return (NULL);
    return (envp[i]);
}

void    path_parsing(t_pipex *pipex, char **envp)
{
    char    *path_temp;
    char    *path_env;

    path_temp = find_path_var(envp);
    if (path_temp)
    {
        path_env = ft_substr(path_temp, 5, ft_strlen(path_temp));
        pipex->paths = ft_split(path_env, ':');
        free(path_env);
    }
    else
        pipex->paths = NULL;
}
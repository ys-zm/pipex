#include "pipex.h"

static char    *find_path_var(char **envp)
{
    size_t i;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
        i++;
    return (envp[i]);
}

void    add_to_elements(int size, t_cmd **pipex, char *path_env, char **cmd_paths)
{
    int     i;

    i = 0;
    while (i < size)
    {
        (*pipex)[i].path_env = path_env;
        (*pipex)[i].cmd_paths = cmd_paths;
        i++;
    }
}

size_t    path_parsing(int size, t_cmd **pipex, char **envp)
{
    char    *path_temp;
    char    *path_env;
    char    **cmd_paths;

    path_temp = find_path_var(envp);
    if (path_temp)
    {
        path_env = ft_substr(path_temp, 5, ft_strlen(path_temp));
        cmd_paths = ft_split(path_env, ':');
        add_to_elements(size, pipex, path_env, cmd_paths);
        return (0);
    }
    return (1);
}
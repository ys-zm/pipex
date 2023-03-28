#include "pipex.h"
//ft_split ":"

char    *find_path_var(t_pip pipex, char **envp)
{
    size_t i;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
        i++;
    return (envp[i]);
}

void    path_parsing(t_pip vars, char **envp)
{
    vars->paths = ft_split(find_path_var(envp), ":");
}
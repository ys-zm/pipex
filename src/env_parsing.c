#include "pipex.h"
//ft_split ":"

char    *find_path_var(char **envp)
{
    size_t i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PATH", 4))
            break ;
        i++;
    }
    return (envp[i]);
}

void    path_parsing(t_var vars, char **envp)
{
    vars->paths = ft_split(find_path_var(envp), ":");
}
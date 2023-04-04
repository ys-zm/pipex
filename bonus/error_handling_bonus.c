#include "pipex_bonus.h"

void    ft_error_msg(const char *str, int error)
{
    perror(str);
    exit(error);
}

void    exit_pipes(t_pipex *pipex)
{
    exit(pipex->status);
}
#include "pipex.h"

void    ft_error_msg(const char *str, int error)
{
    perror(str);
    exit(error);
}

void    exit_pipes(int status)
{
    exit(status);
}
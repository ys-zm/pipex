#include "pipex_bonus.c"

void    ft_error_msg(const char *str, int error)
{
    perror(str);
    exit(error);
}
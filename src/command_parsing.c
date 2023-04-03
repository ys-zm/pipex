#include "pipex.h"

char  **separate_command_args(char *str)
{
    char    **cmd_and_args;

    cmd_and_args = ft_split(str, ' ');
    return (cmd_and_args);
}

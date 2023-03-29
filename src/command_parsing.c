#include "pipex.h"

char  **separate_command_args(char *str)
{
    char    **cmd_and_args;
    size_t  i;

    i = 0;
    cmd_and_args = ft_split(str, ' ');
    while (i < 5)
    {
        printf("%s\n", cmd_and_args[i]);
        i++;
    }
    return (cmd_and_args);
}

void    parse_commands(int size, t_cmd **pipex, char **argv)
{
    int i;
    int j;

    i = 0;
    j = 2;
    while (i < size)
    {
        (*pipex)[i].cmd_and_args = separate_command_args(argv[j]);
        i++;
        j++;
    }
}


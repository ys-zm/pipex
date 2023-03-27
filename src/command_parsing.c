#include "pipex.h"

size_t  count_commands(char **argv)
{
    size_t  count;
    size_t  i;

    count = 0;
    i = 2;
    while (argv[i++])
        count++;
    return (count);
}

size_t  count_strings(char *str)
{

}

char    **separate_command_flags(char *str)
{
    char    *command_flags;

    commands_flags = ft_split(str, " ");
    return (command_flags);
}

char    **parse_commands(char **argv)
{
    size_t   i;
    size_t  command_count;
    char    **command_flags
    
    command_count = count_commands(argv);
    i = 2;
    while (i < count_commands)
    {

    }

}
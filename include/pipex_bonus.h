#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h> //there are a list of error codes in here ; what the error codes mean
#include <stddef.h>
#include "libft.h"
#include <fcntl.h>

# define READ 0
# define WRITE 1

typedef struct s_cmd
{
    char    *cmd_path;
    char    **args;
    int     *fd_in;
    int     *fd_out;
}   t_cmd;

size_t  path_parsing(int size, t_cmd **pipex, char **envp);
void    parse_commands(int size, t_cmd **pipex, char **argv);

#endif

//open files and create outfile if it doesnt exist
//dup2//exec v

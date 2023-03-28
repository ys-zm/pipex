#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h> //there are a list of error codes in here ; what the error codes mean


# define READ 0
# define WRITE 1

typedef struct s_pip
{
    char    *path_env;
    char    **cmd_paths;
    char    *infile;
    char    *outfile;
}   t_pip;


#endif
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

typedef struct s_fd
{
    int fd[2];
}   t_fd;

typedef struct s_cmd
{
    char    **args;
}   t_cmd;

typedef struct s_pipex
{
    char    **paths;
    t_cmd   *cmds;
    int     fd_in;
    int     fd_out;
    // int     **pipes;
    int     *pid;
    int     size;
    t_fd    *pipes;
    int     fd_out_pos;
}   t_pipex;

void    path_parsing(t_pipex *pipex, char **envp);
void    parse_commands(int size, t_cmd **pipex, char **argv);
void    ft_error_msg(const char *str, int error);
void    common_child_actions(t_pipex *pipex, char **envp, int pos);
void    process_management(t_pipex *pipex, char **envp, char **argv);

void    first_child(t_pipex *pipex, char **envp);
void    mid_child(t_pipex *pipex, char **envp, int pos);
void    last_child(t_pipex *pipex, char **envp, int pos, char **argv);

char	*check_access(t_pipex *pipex, int pos);
void    common_child_actions(t_pipex *pipex, char **envp, int pos);

void    print_array(char **array);

#endif

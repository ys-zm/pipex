#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h> //there are a list of error codes in here ; what the error codes mean
#include <stddef.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>

# define READ 0
# define WRITE 1


char    **path_parsing(char **envp);
char    **separate_command_args(char *str);
void    ft_error_msg(const char *str, int error);
void	child_one(int *fd, int fd_in, char **argv, char **envp);
void	child_two(int *fd, int fd_out, char **argv, char **envp);
void    exit_pipes(int status);


#endif
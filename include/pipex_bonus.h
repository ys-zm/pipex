#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

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
    pid_t     *pid;
    int     size;
    t_fd    *pipes;
    int     fd_out_pos;
    int     status;

}   t_pipex;

// Function To Initialize Command/ Arguments, Pid's and Pipes - init_bonus.c
void	ft_init(t_pipex *pipex, char **argv);
void	separate_cmd_arguments(t_pipex *pipex, char **argv);

// Functions to Check Access to Command - check_access_bonus.c
char	*check_env_paths(char **env_path, char *cmd);
char	*check_current_directory(char *cmd);
char	*check_access(t_pipex *pipex, int pos);

// Functions for Process Management, Management of Child Process - process_bonus.c
void    process_management(t_pipex *pipex, char **envp, char **argv);
void    parent_process(t_pipex *pipex, char **envp, char **argv);
void    wait_for_children(t_pipex *pipex);
void    close_pipes(t_pipex *pipex);

// Child Process Functions - children_bonus.c
void    first_child(t_pipex *pipex, char **envp, char *file_in);
void    mid_child(t_pipex *pipex, char **envp, int pos);
void    last_child(t_pipex *pipex, char **envp, int pos, char **argv);
void    common_child_actions(t_pipex *pipex, char **envp, int pos);

// Path Parsing Function - parsing_bonus.c
void    path_parsing(t_pipex *pipex, char **envp);

//Error Handling Functions - error_handling_bonus.c
void    ft_error_msg(const char *str, int error);
void    exit_pipes(t_pipex *pipex);
void    print_array(char **array);

#endif
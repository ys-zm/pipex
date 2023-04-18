/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:26:45 by yzaim         #+#    #+#                 */
/*   Updated: 2023/04/18 15:28:11 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stddef.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

# define READ 0
# define WRITE 1
# define IN 0
# define OUT 1

//Main function - pipex.c
//Process Management Function (piping and forking done here) - pipex.c
int		make_pipes(int *files, char **argv, char **envp);

//Parent Process Function - pipex.c
int		parent_process(int *fd, int *files, pid_t child1, pid_t child2);

// Child Process Fuctions - children.c
void	child_one(int *fd, int fd_in, char **argv, char **envp);
void	child_two(int *fd, int fd_out, char **argv, char **envp);
void	exe_cmd(char **cmd, char **envp);

//Parsing Functions - parsing.c
char	**path_parsing(char **envp);
bool	check_empty_str(char *str);
char	**separate_command_args(char *str);

// Error Handling Functions - error_handling.c
void	ft_error_msg(const char *str, int error);
void	exit_pipes(int status);
void	print_array(char **array);
void	malloc_protect(void *var);

// Functions To Check Access To Env Paths
char	*check_access(char **cmd_and_args, char **envp);
char	*check_env_paths(char **env_path, char *cmd);

#endif

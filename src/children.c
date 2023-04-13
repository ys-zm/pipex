#include "pipex.h"

void    print_array(char **array)
{
    int i;

    i = 0;
    while(array[i])
    {
        write(STDERR_FILENO, array[i], ft_strlen(array[i]));
        write(STDERR_FILENO, "\n", 1);
        i++;
    }
}


// char	*check_env_paths(char **env_path, char *cmd)
// {
// 	char	*add_slash;
// 	char	*cmd_path;
// 	int		i;

// 	i = 0;

// 	while (env_path && env_path[i])
// 	{
// 		add_slash = ft_strjoin(env_path[i], "/");
// 		cmd_path = ft_strjoin(add_slash, cmd);
// 		free(add_slash);
// 		if (!access(cmd_path, X_OK))
// 			return (cmd_path);
// 		free(cmd_path);
// 		i++;
// 	}
// 	return (NULL);
// }

//fix path return...returns  weird path when it is a relative path from the curr directory
//even if relative path is wrong, return is 0 or 1
char	*check_access(char **cmd, char **envp)
{
	char	**env_path;
	char	*add_slash;
	char	*cmd_path;
	int		i;

	i = 0;

	env_path = path_parsing(envp);
	// cmd_path = check_env_paths(env_path, cmd[0]);
	write(STDERR_FILENO, cmd[0], 30);
	write(STDERR_FILENO, "\n", 1);
	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	while (env_path && env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(add_slash, cmd[0]);
		free(add_slash);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	write(STDERR_FILENO, "here!", 5);
	if (!env_path)
	{
		cmd_path = ft_strjoin("./", cmd[0]);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
	}
	// if (cmd_path)
	// 	free(cmd_path);
	free(env_path);
	return (NULL);
}

//even if command is not found, it return a 0.
void	exe_cmd(char **cmd, char **envp)
{
	char	*cmd_path;
	
	cmd_path = check_access(cmd, envp);
	write(STDERR_FILENO, cmd_path, 50);
	write(STDERR_FILENO, "\n", 1);
	execve(cmd_path, cmd, envp);
	write(STDERR_FILENO, "HI", 2);
    ft_error_msg(cmd_path, 127);
}

void	child_one(int *fd, int fd_in, char **argv, char **envp)
{
	char	**cmd;

	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd[WRITE], STDOUT_FILENO) == -1)
		ft_error_msg("Error with dup2 in Child One.\n", 1);
	if (close(fd[READ]) == -1 || close(fd_in) == -1)
		ft_error_msg("Error with closing unused fd's in Child One.\n", 1);
	cmd = separate_command_args(argv[2]);
	exe_cmd(cmd, envp);
}

void	child_two(int *fd, int fd_out, char **argv, char **envp)
{
	char	**cmd;

	if (dup2(fd[READ], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1 )
		ft_error_msg("Error with dup2 in Child Two.\n", 1);
	if (close(fd[WRITE]) == -1 || close(fd_out) == -1)
		ft_error_msg("Error with closing unused fd's in Child Two.\n", 1);
	cmd = separate_command_args(argv[3]);
	exe_cmd(cmd, envp);
}
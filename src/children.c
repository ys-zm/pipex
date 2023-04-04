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

char	*check_access(char **cmd, char **envp)
{
	int		i;
	char	*add_slash;
	char	*cmd_path;
	char	**env_path;

	i = 0;
	env_path = path_parsing(envp);
	while (env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(add_slash, cmd[0]);
		free(add_slash);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(env_path);
	return (NULL);
}

void	exe_cmd(char **cmd, char **envp)
{
	char	*cmd_path;
	
	cmd_path = check_access(cmd, envp);
	if (!cmd_path)
		ft_error_msg("Command not found.\n", 1);
	execve(cmd_path, cmd, envp);
    ft_error_msg(cmd_path, 1);
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
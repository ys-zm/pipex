#include "pipex_bonus.h"

void    first_child(t_pipex *pipex, char **envp)
{
    close(pipex->pipes[0].fd[READ]);
    dup2(pipex->fd_in, STDIN_FILENO);
    close(pipex->fd_in);
    dup2(pipex->pipes[0].fd[WRITE], STDOUT_FILENO);
    close(pipex->pipes[0].fd[WRITE]);
    common_child_actions(pipex, envp, 0);
}

void    mid_child(t_pipex *pipex, char **envp, int pos)
{
    close(pipex->pipes[pos - 1].fd[WRITE]);
    close(pipex->pipes[pos].fd[READ]);
    dup2(pipex->pipes[pos - 1].fd[READ], STDIN_FILENO);
    close(pipex->pipes[pos - 1].fd[READ]);
    dup2(pipex->pipes[pos].fd[WRITE], STDOUT_FILENO);
    close(pipex->pipes[pos].fd[WRITE]);
    common_child_actions(pipex, envp, pos);
}

void    last_child(t_pipex *pipex, char **envp, int pos, char **argv)
{
    close(pipex->pipes[pos - 1].fd[WRITE]);
    dup2(pipex->pipes[pos - 1].fd[READ], STDIN_FILENO);
    close(pipex->pipes[pos - 1].fd[READ]);
    pipex->fd_out = open(argv[pipex->size + 2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    dup2(pipex->fd_out, STDOUT_FILENO);
    close(pipex->fd_out);
    common_child_actions(pipex, envp, pos);
}

char	*check_access(t_pipex *pipex, int pos)
{
	int		i;
	char	*add_slash;
	char	*cmd_path;
   
	i = 0;
	while (pipex->paths && pipex->paths[i])
	{
		add_slash = ft_strjoin(pipex->paths[i], "/");
		cmd_path = ft_strjoin(add_slash, pipex->cmds[pos].args[0]);
		free(add_slash);
		if (!access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void    common_child_actions(t_pipex *pipex, char **envp, int pos)
{
    char    *cmd_path;
    cmd_path = check_access(pipex, pos);
    if (!cmd_path)
		ft_error_msg("Command not found.\n", 127);
	execve(cmd_path, pipex->cmds[pos].args, envp);
    ft_error_msg(cmd_path, 1);
}
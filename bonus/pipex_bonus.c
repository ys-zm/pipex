#include "pipex_bonus.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size - 1)
	{
		if (pipe(pipex->pipes[i].fd) == -1)
			ft_error_msg("Opening pipes failed.\n", 1);
		i++;
	}
}

char  **separate_command_args(char *str)
{
    char    **cmd_and_args;

    cmd_and_args = ft_split(str, ' ');
    return (cmd_and_args);
}

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

void	separate_cmd_arguments(t_pipex *pipex, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (i < pipex->size)
	{
		pipex->cmds[i].args = ft_split(argv[j], ' ');
		i++;
		j++;
	}
}

void	ft_init(t_pipex *pipex, char **argv)
{
	
	pipex->pid = malloc(sizeof(int) * pipex->size);
	pipex->pipes = malloc(sizeof(t_fd) * pipex->size - 1);
	pipex->cmds = malloc(sizeof(t_cmd) * pipex->size);
	separate_cmd_arguments(pipex, argv);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	
	if (argc < 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		return (1);
	}
	pipex.fd_in = open(argv[1], O_RDONLY);
	if (pipex.fd_in == -1)
		ft_error_msg("Failed to open infile.\n", 1);
	pipex.size = argc - 3;
	path_parsing(&pipex, envp);
	ft_init(&pipex, argv);
	create_pipes(&pipex);
	parent_process(&pipex, envp, argv);
	exit_pipes(&pipex);
}
#include "pipex_bonus.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->size)
	{
		if (pipe(pipex->pipes[i]) == -1)
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

size_t	check_if_args(char *str)
{
	while (*str && *str != ' ')
		str++;
	if (*str && *str == ' ')
		return (1);
	return (0);

}

void	ft_init(t_pipex *pipex, int n_of_cmds, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	pipex->size = n_of_cmds;
	pipex->pipes = malloc(sizeof(int) * n_of_cmds * 2);
	pipex->cmds = malloc(sizeof(t_cmd) * n_of_cmds);
	pipex->pid = malloc(sizeof(int) * n_of_cmds);
	while (i < n_of_cmds)
	{
		if (check_if_args(argv[j]))
			pipex->cmds[i].args = ft_split(argv[j], ' ');
		else
			pipex->cmds[i].args[0] = argv[j];
		i++;
		j++;
	}
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
	ft_init(&pipex, argc - 3, argv);
	create_pipes(&pipex);
	process_management(&pipex, envp);
}
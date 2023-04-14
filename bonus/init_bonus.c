#include "pipex_bonus.h"

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
	
	pipex->pid = malloc(sizeof(pid_t) * pipex->size);
	pipex->pipes = malloc(sizeof(t_fd) * pipex->size - 1);
	pipex->cmds = malloc(sizeof(t_cmd) * pipex->size);
	separate_cmd_arguments(pipex, argv);
}
#include "pipex_bonus.h"

char **ft_empty_str(char *str, t_pipex *pipex)
{
	char **arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		malloc_protect(pipex, NULL);
	arr[0] = ft_strdup(str);
	if (!arr[0])
		malloc_protect(pipex, NULL);
	arr[1] = NULL;
	return (arr);
}

void	separate_cmd_arguments(t_pipex *pipex, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (i < pipex->size)
	{
		if (check_empty_str(argv[j]))
			pipex->cmds[i].args = ft_empty_str(argv[j], pipex);
		else
		{
			pipex->cmds[i].args = ft_split(argv[j], ' ');
			if (pipex->cmds[i].args == NULL)
				malloc_protect(pipex, NULL);
		}	
		i++;
		j++;
	}
}

void	ft_init(t_pipex *pipex, char **argv)
{
	
	pipex->pid = malloc(sizeof(pid_t) * pipex->size);
	if (!pipex->pid)
		malloc_protect(pipex, NULL);
	pipex->pipes = malloc(sizeof(t_fd) * pipex->size - 1);
	if (!pipex->pipes)
		malloc_protect(pipex, NULL);
	pipex->cmds = malloc(sizeof(t_cmd) * pipex->size);
	if (!pipex->cmds)
		malloc_protect(pipex, NULL);
	separate_cmd_arguments(pipex, argv);
}
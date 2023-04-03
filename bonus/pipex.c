#include "pipex_bonus.h"

//QUESTIONS
//whats the difference between _execve or execve();

// size_t	make_pipes(void)
// {
// 	//pipe and fork here.
// 	// return back to the parent after the execution of each command

// 	int	fd[2];
// 	int	parent;

// 	if (pipe(fd) == -1)
// 	{
// 		printf("Problem with creating pipes.\n");
// 		return (1);
// 	}
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	parent = fork();
// 	if (!parent)
// 	{
// 		close(fd[0]);
// 		//Child Process
// 	}
// 	else
// 	{
// 		//Parent Process
// 		close(STDOUT_FILENO);
// 	}
// }

//access() to check if the function exists
int main(int argc, char **argv, char **envp)
{
	t_cmd	*pipex;
	int		size;
	int		i;
	int		j;
	
	j = 0;
	i = 0;
	if (argc < 5)
	{
		ft_printf("Wrong input.\n");
		ft_printf("Usage: ./pipex <infile> <cmd1> ... <cmdn> <outfile>\n");
		return (1);
	}

	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		perror("open");
	size = argc - 3;
	pipex = ft_calloc(size, sizeof(t_cmd));
	path_parsing(size, &pipex, envp);
	parse_commands(size, &pipex, argv);

	while (i < size)
	{
		j = 0;
		printf("%d: ", i);
		while (j < 2)
		{
			printf("%s\n", pipex[i].cmd_and_args[j]);
			j++;
		}
		i++;
	}
}
#include "pipex.h"
#include <stddef.h>


//QUESTIONS
//whats the difference between _execve or execve();

//compares not more than n characters.
//return int >, + or < 0. - if s1 is >, + < s2.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*(unsigned char *)s1 == 0 || *(unsigned char *)s2 == 0)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	make_pipes(void)
{
	//pipe and fork here.
	// return back to the parent after the execution of each command

	int	fd[2];
	int	parent;

	if (pipe(fd) == -1)
	{
		printf("Problem with creating pipes.\n");
		return (1);
	}
	parent = fork();
	if (!parent)
	{
		//Child Process
	}
	else
	{
		//Parent Process
	}


	
}

//add ft_printf that i coded
//access() to check if the function exists
int main(int argc, char **argv, char **envp)
{
	t_pip	pipex;

	if (argc < 5)
		write("Wrong input.\n", 13);
	path_parsing
}
#include "pipex_bonus.h"


void    close_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->size)
    {
        close(pipex->pipes[i].fd[READ]);
        close(pipex->pipes[i].fd[WRITE]);
        i++;
    }
}

void    parent_process(t_pipex *pipex)
{
    close_pipes(pipex);
    wait(NULL);
}

void    process_management(t_pipex *pipex, char **envp, char **argv)
{
    int i;

    i = 0;
    printf("first c pos: %d\n", i);
    pipex->pid[i] = fork();
    if (pipex->pid[i] == 0)
        first_child(pipex, envp);
   else
   {
    i++;
    while (i < pipex->size - 1)
    {
        printf("mid c pos: %d\n", i);
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
            mid_child(pipex, envp, i);
        i++;
    }
   } 
    if (i == pipex->size - 1)
    {
        printf("last c pos: %d\n", i);
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
            last_child(pipex, envp, i, argv);
    }
    parent_process(pipex);
}
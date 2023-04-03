#include "pipex_bonus.c"


void    close_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->size)
        close(*(pipex)->pipes[i++]);
}

void    parent_process(t_pipex *pipex)
{
    close_pipes(pipex);
    wait(NULL);
}

void    process_management(t_pipex *pipex, char **envp)
{
    int i;

    i = 0;
    if (i == 0)
        pipex->pid[i++] = fork();
    if (pipex->pid[0] == 0)
        first_child(pipex, envp);
    while (i < pipex->size - 1)
    {
        pipex->pid[i] = fork();
        mid_child(pipex, envp, i);
        i++;
    }
    if (i == pipex->size - 1)
    {
        pipex->pid[i] = fork();
        last_child(pipex, envp, i);
    }
    parent_process(pipex);
}
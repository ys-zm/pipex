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

void    wait_for_children(t_pipex *pipex)
{
    int i;
    int status;

    i = 0;
    while (i < pipex->size)
    {
        waitpid(pipex->pid[i], &status, 0);
        if (WIFEXITED(status))
            pipex->status = WEXITSTATUS(status);
        i++;
    }
}

void    parent_process(t_pipex *pipex, char **envp, char **argv)
{
    process_management(pipex, envp, argv);
    close_pipes(pipex);
    wait_for_children(pipex);

}

void    process_management(t_pipex *pipex, char **envp, char **argv)
{
    int i;

    i = 0;
    pipex->pid[i] = fork();
    if (pipex->pid[i] == 0)
        first_child(pipex, envp);
   else
   {
    i++;
    while (i < pipex->size - 1)
    {
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
            mid_child(pipex, envp, i);
        i++;
    }
   } 
    if (i == pipex->size - 1)
    {
        pipex->pid[i] = fork();
        if (pipex->pid[i] == 0)
            last_child(pipex, envp, i, argv);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 15:45:01 by yzaim         #+#    #+#                 */
/*   Updated: 2023/03/23 17:55:29 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

// int main(void)
// {
//     int fd = open("jo", O_RDWR);
//     char *cmd[] = {"/usr/bin/wc", NULL};
//     char *cmd1[] = {"/bin/echo", "something", NULL};
//     int p[2];
//     // dup2(fd, 0);
//     // char buffer[10];
//     // read(fd, buffer, 5);
//     // buffer[5] = '\0';
//     pipe(p);
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         close(p[1]);
//         dup2(p[0], 0);
//         close(p[0]);
//         execve(cmd[0], cmd, NULL);
//         exit(0);
//     }
//     close(p[0]);
//     dup2(p[1], 1);
//     close(p[1]);
//     execve(cmd1[0], cmd1, NULL);
// }

int main(void)
{
    int p[2];
    char buffer[3];
    pid_t pid2;
    
    pipe(p);
    pid_t pid = fork();
    if (pid > 0)
        pid2 = fork();
    else
    {
        close(p[0]);
        write(p[1], "AC", 2);
        close(p[1]);
        //child 1
        exit(0);
    }
    if (pid2 == 0)
    {
        close(p[0]);
        write(p[1], "B", 1);
        close(p[1]);
        //child 2
        exit(0);
    }
    close(p[1]);
    read(p[0], buffer, 3);
    printf("buffer: %s\n", buffer);
    read(p[0], buffer, 3);
    close(p[0]);
    buffer[2] = '\0';
    printf("buffer: %s\n", buffer);
}

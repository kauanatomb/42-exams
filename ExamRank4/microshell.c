#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return 1;
}

int cd_cmd(char **argv, int i)
{
    if (i != 2)
        return err("error: cd: bad arguments\n");
    else if (chdir(argv[1]) == -1)
        return err("error: cd: cannot change directory to "), err(argv[1]), err("\n");
    return 0;
}

void prev_fd_exist(int *prev_fd)
{
    if (*prev_fd != -1)
    {
        dup2(*prev_fd, 0);
        close(*prev_fd);
    }
    
}

int setup_pipe_for_child(int fd[2])
{
    if (dup2(fd[1], 1) == -1)
        return err("error: fatal\n");
    close(fd[0]);
    close(fd[1]);
    return 0;
}

int exec(char **argv, char **envp, int i, int *prev_fd)
{
    int fd[2];
    int status;
    int has_pipe = argv[i] && strcmp(argv[i], "|") == 0;
    pid_t pid;

    if (has_pipe && pipe(fd) == -1)
        return err("error: fatal\n");
    pid = fork();
    if (pid == -1)
        return err("error: fatal\n");
    if (pid == 0)
    {
        argv[i] = NULL;
        prev_fd_exist(prev_fd);
        if (has_pipe && setup_pipe_for_child(fd))
        {
            err("error: fatal\n");
            exit(1);
        }
        execve(*argv, argv, envp);
        err("error: cannot execute ");
        err(*argv);
        err("\n");
        exit(126);
    }
    if (has_pipe)
    {
        close(fd[1]);
        if (*prev_fd != -1)
            close(*prev_fd);
        *prev_fd = fd[0];
    }
    else if (*prev_fd != -1)
    {
        close(*prev_fd);
        *prev_fd = -1;
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return 1;
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    int status = 0;
    int prev_fd = -1;
    if (argc > 1)
    {
        while (argv[i] && argv[++i])
        {
            argv += i;
            i = 0;
            while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
                i++;
            if (strcmp(*argv, "cd") == 0)
                status = cd_cmd(argv, i);
            else if (i)
                status = exec(argv, envp, i, &prev_fd);
        }
    }
    return (status);
}
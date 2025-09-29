#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int err(char *msg)
{
    while (*msg)
        write(2, msg++, 1);
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

int setup_child(int fd[2])
{
    if (dup2(fd[1], 1) == -1)
        return err("error: fatal\n");
    close(fd[1]);
    close(fd[0]);
    return 0;
}

int setup_parent(int fd[2])
{
    if (dup2(fd[0], 0) == -1)
        return err("error: fatal\n");
    close(fd[1]);
    close(fd[0]);
    return 0;
}

int exec_cmd(char **argv, int i, char **envp)
{
    int has_pipe = argv[i] && strcmp(argv[i], "|") == 0;
    int status;
    int fd[2];
    pid_t pid;

    if (has_pipe && pipe(fd) == -1)
        return err("error: fatal\n");
    pid = fork();
    if (pid == -1)
        return err("error: fatal\n");
    if (pid == 0)
    {
        argv[i] = NULL;
        if (has_pipe && setup_child(fd))
        {
            err("error: fatal\n");
            exit(1);
        }
        execve(*argv, argv, envp);
        err("error: cannot execute ");
        err(*argv);
        err("\n");
        exit(127);
    }
    if (has_pipe && setup_parent(fd))
        return err("error: fatal\n");
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

int main(int argc, char **argv, char **envp)
{
    int status = 0;
    int i = 0;
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
                status = exec_cmd(argv, i, envp);
        }
    }
    return (status);
}
#include "gnl.h"

char *ft_strdup(char *str)
{
    int i = 0;
    char *res;
    if (!str)
        return (NULL);
    while (str[i])
        i++;
    res = malloc(i + 1);
    i = 0;
    while (str[i])
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *gnl(int fd)
{
    if (fd < 0 || BUF_SIZE <= 0)
        return (NULL);
    static char buffer[BUF_SIZE];
    char line[70000];
    static int pos = 0;
    static int buf_read = 0;
    int i = 0;
    while (1)
    {
        if (pos >= buf_read)
        {
            buf_read = read(fd, buffer, BUF_SIZE);
            pos = 0;
            if (buf_read <= 0)
                break ;
        }
        line[i] = buffer[pos++];
        if (line[i++] == '\n')
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

#include <fcntl.h>

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *res = " ";
    while (res != NULL)
    {
        res = gnl(fd);
        printf("res: %s\n", res);
        free(res);
    }
    free(res);
    close(fd);
    return (0);
}
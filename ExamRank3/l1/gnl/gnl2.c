#include "gnl.h"

char *ft_strdup(char *str)
{
    if (!str)
        return (NULL);
    int i = 0;
    while (str[i])
        i++;
    char *res = malloc(i + 1);
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
    static char buf[BUF_SIZE];
    char line[70000];
    static int b_read = 0;
    static int read_buf = 0;
    int i = 0;
    while (1)
    {
        if (read_buf >= b_read)
        {
            b_read = read(fd, buf, BUF_SIZE);
            read_buf = 0;
            if (b_read <= 0)
                break ;
        }
        line[i] = buf[read_buf++];
        if (line[i++] == '\n')
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

int main(void)
{
    char *res = " ";
    int fd;
    fd = open("text.txt", O_RDONLY);
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
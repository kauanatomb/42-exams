#include "gnl.h"

char *ft_strdup(char *str)
{
    if (!str)
        return (NULL);
    int i = 0;
    while (str[i])
        i++;
    char *str2 = malloc(i + 1);
    if (!str2)
        return (NULL);
    i = 0;
    while (str[i])
    {
        str2[i] = str[i];
        i++;
    }
    str2[i] = '\0';
    return (str2);
}

char *gnl(int fd)
{
    if (fd < 0 || BUF_SIZE <= 0)
        return (NULL);
    char line[70000];
    static int b_rd = 0;
    static int pos_rd = 0;
    static char buf[BUF_SIZE];
    int i = 0;
    while (1)
    {
        if (pos_rd >= b_rd)
        {
            b_rd = read(fd, buf, BUF_SIZE);
            pos_rd = 0;
            if (b_rd <= 0)
                break ;
        }
        line[i] = buf[pos_rd++];
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
    int fd = open("text.txt", O_RDONLY);
    char *res = " ";
    while (res != NULL)
    {
        res = gnl(fd);
        printf("%s\n", res);
        free(res);
    }
    free(res);
    close(fd);
    return (0);
}
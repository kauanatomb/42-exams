#ifndef BUF_SIZE
# define BUF_SIZE 4
#endif

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char *ft_strdup(char *s)
{
    if (!s)
        return NULL;
    int i = 0;
    while (s[i])
        i++;
    char *str = malloc(i + 1);
    i = 0;
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return str;
}

char *gnl(int fd)
{
    if (fd < 0 || BUF_SIZE <= 0)
        return NULL;
    int i = 0;
    char line[70000];
    static int b_read = 0;
    static int pos = 0;
    static char buf[BUF_SIZE];
    while (1)
    {
        if (pos >= b_read)
        {
            b_read = read(fd, buf, BUF_SIZE);
            if (b_read <= 0)
                break ;
            pos = 0;
        }
        line[i] = buf[pos++];
        if (line[i++] == '\n')
            break ;
    }
    if (i == 0)
        return NULL;
    line[i] = '\0';
    return (ft_strdup(line));
}

int main()
{
    int fd = open("text.txt", O_RDONLY);
    char *res = " ";
    while (res != NULL)
    {
        res = gnl(fd);
        printf("%s", res);
        free(res);
    }
    free(res);
    close(fd);
    return 0;
}
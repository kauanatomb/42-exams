#ifndef BUF_SIZE
# define BUF_SIZE 4
#endif

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *ft_strdup(char *s)
{
    if (!s)
        return NULL;
    int len = 0;
    while (s[len])
        len++;
    char *str = malloc(len + 1);
    len = 0;
    while (s[len])
    {
        str[len] = s[len];
        len++;
    }
    str[len] = '\0';
    return str;
}

char *gnl(int fd)
{
    if (fd < 0 || BUF_SIZE < 0)
        return NULL;
    char line[70000];
    static int pos = 0;
    static int read_b = 0;
    static char buf[BUF_SIZE];
    int i = 0;
    while (1)
    {
        if (pos >= read_b)
        {
            read_b = read(fd, buf, BUF_SIZE);
            pos = 0;
            if (read_b <= 0)
                break ;
        }
        line[i] = buf[pos++];
        if (line[i++] == '\n')
            break ;
    }
    if (i == 0)
        return NULL;
    line[i] = '\0';
    return ft_strdup(line);
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
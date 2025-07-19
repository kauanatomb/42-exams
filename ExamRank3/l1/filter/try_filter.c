#ifndef BUF_SIZE
# define BUF_SIZE 4
#endif

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int str_match(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    if (*s2 == '\0')
        return 1;
    return 0;
}

void    print_starts(int i)
{
    while (i--)
        write(1, "*", 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || BUF_SIZE <= 0)
        return 1;
    char *leftover = NULL;
    int rd;
    char buf[BUF_SIZE];
    int needle_s = strlen(argv[1]);
    while ((rd= read(0, buf, BUF_SIZE)) > 0)
    {
        int len = leftover ? strlen(leftover) : 0;
        int total = rd + len;
        char *tmp = malloc(total + 1);
        if (!tmp)
        {
            free(leftover);
            perror("Error");
            return 1;
        }
        tmp[total] = '\0';
        if (leftover)
        {
            memmove(tmp, leftover, len);
            free(leftover);
        }
        memmove(tmp + len, buf, BUF_SIZE);
        int i = 0;
        while (i < total - needle_s)
        {
            if (str_match(&tmp[i], argv[1]))
            {
                print_starts(needle_s);
                i += needle_s;
            }
            else
            {
                write(1, &tmp[i], 1);
                i++;
            }
        }
        leftover = malloc(total - i + 1);
        if (!leftover)
        {
            free(tmp);
            perror("Error");
            return 1;
        }
        memmove(leftover, &tmp[i], total - i);
        free(tmp);
        leftover[total - i] = '\0';
    }
    if (rd < 0)
    {
        free(leftover);
        perror("Error");
        return 1;
    }
    if (leftover)
    {
        write(1, leftover, strlen(leftover));
        free(leftover);
    }
    return (0);
}
# define BUF_SIZE 4

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int str_match(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s2++;
        s1++;
    }
    if (*s2 == '\0')
        return (1);
    return (0);
}

void    print_stars(int i)
{
    while (i--)
        write(1, "*", 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0' || BUF_SIZE < 1)
        return (1);
    int needle_len = strlen(argv[1]);
    char *leftover = NULL;
    int rd = 0;
    char buf[BUF_SIZE];
    while ((rd= read(0, buf, BUF_SIZE)) > 0)
    {
        int left_len = leftover ? strlen(leftover) : 0;
        int total = rd + left_len;
        char *tmp = malloc(total + 1);
        if (!tmp)
        {
            perror("Error");
            free(leftover);
            return (1);
        }
        if (leftover)
        {
            memmove(tmp, leftover, left_len);
            free(leftover);
        }
        memmove(tmp + left_len, buf, rd);
        tmp[total] = '\0';
        int i = 0;
        while (i < total - needle_len)
        {
            if (str_match(&tmp[i], argv[1]))
            {
                print_stars(needle_len);
                i += needle_len;
            }
            else
            {
                write(1, &tmp[i], 1);
                i++;
            }
        }
        leftover = malloc(total + 1 - i);
        if (!leftover)
        {
            perror("Error");
            free(tmp);
            return (1);
        }
        memmove(leftover, &tmp[i], total - i);
        leftover[total - i] = '\0';
        free(tmp);
    }
    if (rd < 0)
    {
        perror("Error");
        free(leftover);
        return (1);
    }
    if (leftover)
    {
        write(1, leftover, strlen(leftover));
        free(leftover);
    }
    return (0);
}
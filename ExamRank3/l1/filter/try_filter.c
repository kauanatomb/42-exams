#ifndef BUF_SIZE
# define BUF_SIZE 4
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_starts(int len)
{
    while (len--)
        write(1, "*", 1);
}

int str_match(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    if (*s1 == '\0')
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || BUF_SIZE < 0)
        return 1;
    int needle_len = strlen(argv[1]);
    char *buf[BUF_SIZE];
    int read_b;
    char *leftover = NULL;
    while ((read_b= read(0, buf, BUF_SIZE)) > 0)
    {
        int left_len = leftover ? strlen(leftover) : 0;
        int total = read_b + left_len;
        char *tmp = malloc(total + 1);
        if (!tmp)
        {
            free(leftover);
            perror("Error");
            return 1;
        }
        if (leftover)
        {
            memmove(tmp, leftover, left_len);
            free(leftover);
        }
        memmove(tmp + left_len, buf, read_b);
        tmp[total] = '\0';
        int i = 0;
        while (i < total - needle_len)
        {
            if (str_match(argv[1], &tmp[i]))
            {
                print_starts(needle_len);
                i += needle_len;
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
        leftover[total - i] = '\0';
        free(tmp);
    }
    if (read_b < 0)
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
    return 0;
}
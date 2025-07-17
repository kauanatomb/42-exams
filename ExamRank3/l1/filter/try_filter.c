#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUF_SIZE
# define BUF_SIZE 4
#endif

int str_match(char *s, char *s2)
{
    while (*s && *s2 && *s == *s2)
    {
        s++;
        s2++;
    }
    if (*s2 == '\0')
        return 1;
    return 0;
}

void    print_starts(int i)
{
    while(i--)
        write(1, "*", 1);
}

int main (int argc, char *argv[])
{
    if (argc != 2)
        return 1;
    int len = strlen(argv[1]);
    int b_read = 0;
    char *leftover = NULL;
    char *buf[BUF_SIZE];
    while ((b_read = read(0, buf, BUF_SIZE)) > 0)
    {
        int left_len = leftover ? strlen(leftover) : 0;
        int total = left_len + b_read;
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
            memmove(tmp, leftover, left_len);
            free(leftover);
        }
        memmove(tmp + left_len, buf, b_read);
        int i = 0;
        while (i < total - len)
        {
            if (str_match(&tmp[i], argv[1]))
            {
                print_starts(len);
                i += len;
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
    if (b_read < 0)
    {
        perror("Error");
        free(leftover);
        return 1;
    }
    if (leftover)
    {
        write(1, leftover, strlen(leftover));
        free(leftover);
    }
    return 0;
}
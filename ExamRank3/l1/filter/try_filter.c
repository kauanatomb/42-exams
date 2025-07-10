#define BUF_SIZE 4

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int match_str(char *str1, char *str2)
{
    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    if (*str2 == '\0')
        return (1);
    return (0);
}

void    print_starts(int n)
{
    while (n--)
        write(1, "*", 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1][0] == '\0')
        return (1);
    char    buf[BUF_SIZE];
    char    *leftover = NULL;
    int     needle_len = strlen(argv[1]);
    int     rd;

    while ((rd = read(0, buf, BUF_SIZE)) > 0)
    {
        int left_len = leftover ? strlen(leftover) : 0;
        int total = left_len + rd;
        char    *tmp = malloc(total + 1);
        if (!tmp)
        {
            fprintf(stderr, "Error: %s", strerror(errno));
            free(leftover);
            return (1);
        }
        if (leftover)
        {
            memcpy(tmp, leftover, left_len);
            free(leftover);
        }
        memcpy(tmp + left_len, buf, total);
        tmp[total] = '\0';
        int i = 0;
        while (i <= total - needle_len)
        {
            if (match_str(&tmp[i], argv[1]))
            {
                print_starts(needle_len);
                i += needle_len;
            }
            else
                write(1, &tmp[i++], 1);
        }
        leftover = malloc(total + 1 - i);
        if (!leftover)
        {
            fprintf(stderr, "Error: %s", strerror(errno));
            free(tmp);
            return (1);
        }
        memcpy(leftover, &tmp[i], total - i);
        leftover[total - i] = '\0';
        free(tmp);
    }
    if (rd < 0)
    {
        fprintf(stderr, "Error: %s", strerror(errno));
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
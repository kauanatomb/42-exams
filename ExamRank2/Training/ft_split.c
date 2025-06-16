/*
Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/
#include <stdio.h>
#include <stdlib.h>
int     is_space(char c)
{
    return ((c >= 8 && c <= 13) || c == ' ');
}

int     count_words(char *str)
{
    int count = 0;
    while (*str)
    {
        while (is_space(*str) && *str)
            str++;
        if (*str)
        {
            count++;
            while (!is_space(*str) && *str)
                str++;
        }
    }
    return (count);
}

char *fill_words(char *start, int size)
{
    char *str = malloc(size + 1);
    if (!str)
        return (NULL);
    int i = 0;
    while (size > i)
    {
        str[i] = start[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void    *free_strs(char **strs, int size)
{
    int i = 0;
    while (i < size)
    {
        free(strs[i++]);
    }
    free(strs);
    return (NULL);
}

char    **ft_split(char *str)
{
    if (!str)
        return (NULL);
    int counted_words = count_words(str);
    char **strs = malloc((counted_words + 1) * sizeof(char *));
    if (!strs)
        return (NULL);
    char *start;
    int i = 0;
    while (*str)
    {
        while (is_space(*str) && *str)
            str++;
        start = str;
        if (*str)
        {
            while (!is_space(*str) && *str)
                str++;
            strs[i] = fill_words(start, str - start);
            if (!strs[i])
                free_strs(strs, i);
            i++;
        }
    }
    strs[i] = NULL;
    return (strs);
}

int main()
{
    char **result = ft_split("ola kauana");
    if (!result)
        return (0);
    int i = 0;
    while (result[i])
    {
        printf("%s\n", result[i++]);
    }
    free_strs(result, i);
    return (0);
}
/*
Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/

#include <stdlib.h>

int is_space(char c)
{
    return ((c >= 8 && c <= 13) || c == ' ');
}

int count_words(char *str)
{
    int count = 0;
    while (*str)
    {
        while(is_space(*str) && *str)
            str++;
        if (!is_space(*str) && *str)
        {
            count++;
            while (!is_space(*str) && *str)
                str++;
        }
    }
    return (count);
}

char *fill_word(char *str, int size)
{
    int i = 0;
    char *str2 = malloc(size + 1);
    if (!str2)
        return (NULL);
    while (i < size)
    {
        str2[i] = str[i];
        i++;
    }
    str2[i] = '\0';
    return (str2);
}

void    *free_result(char **strs, int size)
{
    int i = 0;
    while (i < size)
    {
        free(strs[i]);
        i++;
    }
    free(strs);
    return (NULL);
}

char    **ft_split(char *str)
{
    if (!str)
        return (NULL);
    char *start;
    int i = 0;
    int word_counted = count_words(str);
    char **result = malloc((word_counted + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while (*str)
    {
        while (is_space(*str) && *str)
            str++;
        if (!is_space(*str) && *str)
        {
            start = str;
            while (!is_space(*str) && *str)
                str++;
            result[i] = fill_word(start, str - start);
            if (!result[i])
                free_result(result, i);
            i++;
        }
    }
    result[i] = NULL;
    return (result);
}

#include <stdio.h>
int main()
{
    int i = 0;
    char **result = ft_split("kauana tombolato silva");
    if (!result)
        return (0);
    while (result[i])
    {
        printf("%s\n", result[i++]);
    }
    free_result(result, i);
    return (0);
}
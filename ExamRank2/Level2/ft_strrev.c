/*
Write a function that reverses (in-place) a string.

It must return its parameter.

Your function must be declared as follows:

char    *ft_strrev(char *str);
*/

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strrev(char *str)
{
    int start = 0;
    int tail = ft_strlen(str) - 1;
    char c = 0;
    while (start <= tail)
    {
        c = str[start];
        str[start] = str[tail];
        str[tail] = c;
        start++;
        tail--;
    }
    return (str);
}

// #include <stdio.h>
// int main(void)
// {
//     char str[] = "hellow world";
//     printf("%s\n", ft_strrev(str));
//     return (0);
// }
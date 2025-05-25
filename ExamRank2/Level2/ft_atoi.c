/*
Write a function that converts the string argument str to an integer (type int)
and returns it.

It works much like the standard atoi(const char *str) function, see the man.

Your function must be declared as follows:

int	ft_atoi(const char *str);
*/

int ft_atoi(const char *str)
{
    int i = 1;
    int n = 0;

    while ((*str >= 8 && 13 >= *str) || *str == ' ')
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            i = -1;
        str++;
    }
    while (*str >= '0' && '9' >= *str)
    {
        n *= 10;
        n = n + (*str - '0');
        str++;
    }
    return (n * i);
}

// #include <stdio.h>
// #include <limits.h>
// int main(void)
// {
//     printf("%d", ft_atoi("-2147483648"));
//     return (0);
// }
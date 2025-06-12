/*
Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);
*/

#include <stdlib.h>
#include <stdio.h>
int     ft_nbr_len(int nbr)
{
    int count = 0;
    if (nbr <= 0)
        count++;
    while (nbr != 0)
    {
        nbr = nbr / 10;
        count++;
    }
    return (count);
}

char    *ft_itoa(int nbr)
{
    int len = ft_nbr_len(nbr);
    char *str = malloc(len + 1);
    if (!str)
        return (0);
    str[len] = '\0';
    if (nbr < 0)
    {
        nbr = -nbr;
        str[0] = '-';
    }
    if (nbr == 0)
        str[0] = '0';
    len--;
    while (nbr > 0)
    {
        str[len--] = (nbr % 10) + '0';
        nbr = nbr / 10;
    }
    return (str);
}

int main(void)
{
    int num = -12345;
    char *result = ft_itoa(num);
    if (result)
    {
        printf("The integer %d as a string is: %s\n", num, result);
        free(result);
    }
    return 0;
}
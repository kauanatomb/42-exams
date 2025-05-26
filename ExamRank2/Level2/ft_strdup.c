/*
Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
*/
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return (s1);
}

char    *ft_strdup(char *src)
{
    int count = ft_strlen(src);
    char *str = malloc(count + 1);
    if (!str)
        return (NULL);
    return (ft_strcmp(str, src));
}

// int main(void)
// {
//     printf("%s", ft_strdup("Kauana123456"));
//     return (0);
// }
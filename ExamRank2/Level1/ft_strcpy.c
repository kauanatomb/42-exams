/*
Reproduce the behavior of the function strcpy (man strcpy).

Your function must be declared as follows:

char    *ft_strcpy(char *s1, char *s2);
*/

char    *ft_strcpy(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return (s1);
}
/*
#include <stdio.h>
int main()
{
    char    dest[10];
    printf("%s", ft_strcpy(dest, "hello"));
}
*/
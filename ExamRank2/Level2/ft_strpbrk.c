/*
Reproduce exactly the behavior of the function strpbrk
(man strpbrk).

The function should be prototyped as follows:

char	*ft_strpbrk(const char *s1, const char *s2);
*/

char    *ft_strpbrk(const char *s1, const char *s2)
{
    int i = 0;
    while (*s1)
    {
        i = 0;
        while (s2[i])
        {
            if (*s1 == s2[i])
                return ((char *)s1);
            i++;
        }
        s1++;
    }
    return (0);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
//     printf("%s\n", ft_strpbrk("hello", "u"));
//     printf("%s", strpbrk("hello", "u"));
//     return (0);
// }
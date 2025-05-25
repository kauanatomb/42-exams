/*
Reproduce exactly the behavior of the function strcspn
(man strcspn).

The function should be prototyped as follows:

size_t	ft_strcspn(const char *s, const char *reject);
*/

#include <string.h>
size_t	ft_strcspn(const char *s, const char *reject)
{
    size_t i = 0;
    int j = 0;
    while (s[i])
    {
        j = 0;
        while (reject[j])
        {
            if (s[i] == reject[j])
                return (i);
            j++;
        }
        i++;
    }
    return (i);
}

// #include <stdio.h>
// int main(void)
// {
//     printf("%lu\n", strcspn("kauana", "m"));
//     printf("%lu", ft_strcspn("kauana", "m"));
//     return (0);
// }
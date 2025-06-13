/*
Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$>
*/
#include <unistd.h>
#include <stdio.h>
int ft_atoi(char *str)
{
    int result = 0;
    while (*str)
    {
        result *= 10;
        result = result + *str - '0';
        str++;
    }
    return (result);
}

int is_prime(int n)
{
    int i = 2;
    if (n < i)
        return (0);
    while (n > i)
    {
        if (n % i == 0)
            return (0);
        i++;
    }
    return (1);
}

void    ft_putstr(int n)
{
    if (n > 9)
        ft_putstr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

int main(int argc, char *argv[])
{
    int sum = 0;
    if (argc == 2)
    {
        int n = ft_atoi(argv[1]);
        int i = 2;
        if (n > 0 && n > 1)
        {
            while (i <= n)
            {
                if (is_prime(i))
                    sum += i;
                i++;
            }
        }
    }
    ft_putstr(sum);
    write(1, "\n", 1);
    return (0);
}
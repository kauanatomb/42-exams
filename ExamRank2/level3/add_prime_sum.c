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

int ft_str_to_nb(char *str)
{
    int nb = 0;
    while (*str)
    {
        nb *= 10;
        nb = nb + (*str - 48);
        str++;
    }
    return (nb);
}

void ft_putnbr(int nbr)
{
    if (nbr > 9)
        ft_putnbr(nbr/10);
    write(1, &"0123456789"[nbr % 10], 1);
}

int is_prime(int n)
{
    int i = 2;
    if (n < 2)
        return (0);
    while (n > i)
    {
        if (n % i == 0)
            return (0);
        i++;
    }
    return (1);
}

#include <stdio.h>
int main(int argc, char *argv[])
{
    int i = 2;
    int nbr = ft_str_to_nb(argv[1]);
    int sum = 0;
    if (argc == 2 && nbr > 0)
    {
        while (nbr >= i)
        {
            if (is_prime(i))
            {
                sum += i;
            }
            i++;
        }
    }
    ft_putnbr(sum);
    write(1, "\n", 1);
    return (0);
}
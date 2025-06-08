/*
Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.

Examples:

$> ./pgcd 42 10 | cat -e
2$
$> ./pgcd 42 12 | cat -e
6$
$> ./pgcd 14 77 | cat -e
7$
$> ./pgcd 17 3 | cat -e
1$
$> ./pgcd | cat -e
$
*/
#include <unistd.h>
#include <stdlib.h>

int common(int n1, int n2)
{
    int denominator;
    if (n1 < n2)
        denominator = n1;
    else 
        denominator = n2;
    while (denominator > 0)
    {
        if (n1 % denominator == 0 && n2 % denominator == 0)
            return (denominator);
        denominator--;
    }
    return (1);
}

void    ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
        ft_putnbr(common(atoi(argv[1]), atoi(argv[2])));
    write(1, "\n", 1);
    return (0);
}
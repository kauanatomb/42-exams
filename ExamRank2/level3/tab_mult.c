/*
Write a program that displays a number's multiplication table.

The parameter will always be a strictly positive number that fits in an int,
and said number times 9 will also fit in an int.

If there are no parameters, the program displays \n.

Examples:

$>./tab_mult 9
1 x 9 = 9
2 x 9 = 18
3 x 9 = 27
4 x 9 = 36
5 x 9 = 45
6 x 9 = 54
7 x 9 = 63
8 x 9 = 72
9 x 9 = 81
$>./tab_mult 19
1 x 19 = 19
2 x 19 = 38
3 x 19 = 57
4 x 19 = 76
5 x 19 = 95
6 x 19 = 114
7 x 19 = 133
8 x 19 = 152
9 x 19 = 171
$>
$>./tab_mult | cat -e
$
$>
*/
#include <unistd.h>
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

void ft_putnbr(int n)
{
    if (n > 9)
        ft_putnbr(n / 10);
    write(1, &"0123456789"[n % 10], 1);
}

void tab_mult(int n)
{
    int i = 1;
    while (i < 10)
    {
        write(1, &"0123456789"[i % 10], 1);
        write(1, &" ", 1);
        write(1, &"x", 1);
        write(1, &" ", 1);
        ft_putnbr(n);
        write(1, &" ", 1);
        write(1, &"=", 1);
        write(1, &" ", 1);;
        ft_putnbr(i * n);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        tab_mult(ft_atoi(argv[1]));
    else
        write(1, "\n", 1);
    return (0);
}
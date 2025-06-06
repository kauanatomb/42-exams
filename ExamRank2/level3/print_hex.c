/*
Write a program that takes a positive (or zero) number expressed in base 10,
and displays it in base 16 (lowercase letters) followed by a newline.

If the number of parameters is not 1, the program displays a newline.

Examples:

$> ./print_hex "10" | cat -e
a$
$> ./print_hex "255" | cat -e
ff$
$> ./print_hex "5156454" | cat -e
4eae66$
$> ./print_hex | cat -e
$
*/
#include <unistd.h>
void   print_hex(int n)
{
    if (n >= 16)
        print_hex(n/16);
    write(1, &"0123456789abcdef"[n%16], 1);
}

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

int main(int argc, char *argv[])
{
    if (argc == 2)
        print_hex(ft_atoi(argv[1]));
    write(1, "\n", 1);
    return (0);
}
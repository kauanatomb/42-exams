/*
Write a program that takes a string and displays this string after rotating it
one word to the left.

Thus, the first word becomes the last, and others stay in the same order.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

Words will be separated by only one space in the output.

If there's less than one argument, the program displays \n.

Example:

$>./rostring "abc   " | cat -e
abc$
$>
$>./rostring "Que la      lumiere soit et la lumiere fut"
la lumiere soit et la lumiere fut Que
$>
$>./rostring "     AkjhZ zLKIJz , 23y"
zLKIJz , 23y AkjhZ
$>
$>./rostring "first" "2" "11000000"
first
$>
$>./rostring | cat -e
$
$>
*/
#include <unistd.h>

int is_space(char c)
{
    return ((c >= 8 && c <= 13) || c == ' ');
}

int main(int argc, char *argv[])
{
    char *str = argv[1];
    int i = 0;
    int start = 0;
    int end = 0;
    if (argc > 1)
    {
        if (str[i])
        {
            while (is_space(str[i]) && str[i])
                i++;
            start = i;
            while (!is_space(str[i]) && str[i])
                i++;
            end = i;
            while (is_space(str[i]) && str[i])
                i++;
        }
        while (str[i])
        {
            while (!is_space(str[i]) && str[i])
                write(1, &str[i++], 1);
            while (is_space(str[i]) && str[i])
                i++;
            write(1, " ", 1);
        }
        if (str[i] == '\0')
        {
            while (start < end)
            {
                write(1, &str[start++], 1);
            }
        }
    }
    write(1, "\n", 1);
    return (0);
}
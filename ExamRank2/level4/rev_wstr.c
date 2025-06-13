/*
Write a program that takes a string as a parameter, and prints its words in
reverse order.

A "word" is a part of the string bounded by spaces and/or tabs, or the
begin/end of the string.

If the number of parameters is different from 1, the program will display
'\n'.

In the parameters that are going to be tested, there won't be any "additional"
spaces (meaning that there won't be additionnal spaces at the beginning or at
the end of the string, and words will always be separated by exactly one space).

Examples:

$> ./rev_wstr "You hate people! But I love gatherings. Isn't it ironic?" | cat -e
ironic? it Isn't gatherings. love I But people! hate You$
$>./rev_wstr "abcdefghijklm"
abcdefghijklm
$> ./rev_wstr "Wingardium Leviosa" | cat -e
Leviosa Wingardium$
$> ./rev_wstr | cat -e
$
$>
*/

#include <unistd.h>
#include <stdio.h>

int is_space(char c)
{
    return ((c >= 8 && c <= 13) || c == ' ');
}

int main(int argc, char *argv[])
{
    int i = 0;
    if (argc == 2)
    {
        char *str = argv[1];
        if (str[i])
        {
            while (str[i])
                i++;
            i--;
        }
        while (i >= 0)
        {
            while (!is_space(str[i]) && str[i] && i >= 0)
                i--;
            i++;
            while (!is_space(str[i]) && str[i])
                write(1, &str[i++], 1);
            i--;
            while (!is_space(str[i]) && str[i] && i >= 0)
                i--;
            if (is_space(str[i]))
                write(1, " ", 1);
            i--;
        }
    }
    write(1, "\n", 1);
    return (0);
}
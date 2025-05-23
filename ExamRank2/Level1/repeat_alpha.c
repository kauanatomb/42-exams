/*
Write a program called repeat_alpha that takes a string and display it
repeating each alphabetical character as many times as its alphabetical index,
followed by a newline.

'a' becomes 'a', 'b' becomes 'bb', 'e' becomes 'eeeee', etc...

Case remains unchanged.

If the number of arguments is not 1, just display a newline.

Examples:

$>./repeat_alpha "abc"
abbccc
$>./repeat_alpha "Alex." | cat -e
Alllllllllllleeeeexxxxxxxxxxxxxxxxxxxxxxxx.$
$>./repeat_alpha 'abacadaba 42!' | cat -e
abbacccaddddabba 42!$
$>./repeat_alpha | cat -e
$
$>
$>./repeat_alpha "" | cat -e
$
$>
*/
#include <unistd.h>
void    repeat_alpha(char *str)
{
    int i;
    while (*str)
    {
        i = 0;
        if (*str >= 'a' && *str <= 'z')
        {
            i = 96;
            i = *str - i;
            while (i-- > 0)
                write(1, str, 1);
        }
        else if (*str >= 'A' && *str <= 'Z')
        {
            i = 64;
            i = *str - i;
            while (i-- > 0)
                write(1, str, 1);
        }
        else
        {
            write(1, str, 1);
        }
        str++;
    }
}

int    main(int argc, char *argv[])
{
    if (argc == 2)
        repeat_alpha(argv[1]);
    write(1, "\n", 1);
    return (0);
}
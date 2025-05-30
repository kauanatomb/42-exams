/*
Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat -e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>
*/
#include <unistd.h>

void    last_word(char *s)
{
    while (*s)
        s++;
    s--;
    while ((*s >= 8 && *s <= 13 && *s) || *s == ' ')
        s--;
    while (!((*s >= 8 && *s <= 13) || *s == ' ') && *s)
        s--;
    while (*s)
    {
        write(1, s, 1);
        s++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        last_word(argv[1]);
    write(1, "\n", 1);
    return (0);
}
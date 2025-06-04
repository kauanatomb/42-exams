/*

Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.

Examples:

$> ./expand_str "See? It's easy to print the same thing" | cat -e
See?   It's   easy   to   print   the   same   thing$
$> ./expand_str " this        time it      will     be    more complex  " | cat -e
this   time   it   will   be   more   complex$
$> ./expand_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
$
$> ./expand_str "" | cat -e
$
$>
*/
#include <unistd.h>

int is_space(char c)
{
    return (((c >= 8 && c <= 13) || c == ' '));
}

void    expand_str(char *str)
{
    int first_word = 1;
    while (*str)
    {
        while (*str && is_space(*str))
            str++;
        if (*str)
        {
            if (first_word == 0)
                write(1, "   ", 3);
            first_word = 0;
            while (*str && !is_space(*str))
                write(1, str++, 1);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        expand_str(argv[1]);
    write(1, "\n", 1);
    return (0);
}

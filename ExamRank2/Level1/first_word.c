// Write a program that takes a string and displays its first word, followed by a
// newline.

// A word is a section of string delimited by spaces/tabs or by the start/end of
// the string.

// If the number of parameters is not 1, or if there are no words, simply display
// a newline.

// Examples:

// $> ./first_word "FOR PONY" | cat -e
// FOR$
// $> ./first_word "this        ...    is sparta, then again, maybe    not" | cat -e
// this$
// $> ./first_word "   " | cat -e
// $
// $> ./first_word "a" "b" | cat -e
// $
// $> ./first_word "  lorem,ipsum  " | cat -e
// lorem,ipsum$
// $>

#include <unistd.h>

int is_space(char c)
{
    return((c < 13 && c > 8) || c == 32);
}

int is_not_space(char c)
{
    return (!((c < 13 && c > 8) || c == 32));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (write(1, "\n", 1));
    while (is_space(*argv[1]))
    {
        argv[1]++;
    }
    while (is_not_space(*argv[1]) && *argv[1])
    {
        write(1, argv[1], 1);
        argv[1]++;
    }
    write(1, "\n", 1);
    return (0);
}
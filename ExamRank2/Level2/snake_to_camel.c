/*
Write a program that takes a single string in snake_case format
and converts it into a string in lowerCamelCase format.

A snake_case string is a string where each word is in lower case, separated by
an underscore "_".

A lowerCamelCase string is a string where each word begins with a capital letter
except for the first one.

Examples:
$>./camel_to_snake "here_is_a_snake_case_word"
hereIsASnakeCaseWord
$>./camel_to_snake "hello_world" | cat -e
helloWorld$
$>./camel_to_snake | cat -e
$
*/
#include <unistd.h>

void camel_to_snake(char *str)
{
    while (*str)
    {
        if (*str == '_')
        {
            str++;
            *str -= 32;
        }
        write(1, str, 1);
        str++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        camel_to_snake(argv[1]);
    write(1, "\n", 1);
    return (0);
}
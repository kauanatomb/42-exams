/*
Write a program named hidenp that takes two strings and displays 1
followed by a newline if the first string is hidden in the second one,
otherwise displays 0 followed by a newline.

Let s1 and s2 be strings. We say that s1 is hidden in s2 if it's possible to
find each character from s1 in s2, in the same order as they appear in s1.
Also, the empty string is hidden in any string.

If the number of parameters is not 2, the program displays a newline.

Examples :

$>./hidenp "fgex.;" "tyf34gdgf;'ektufjhgdgex.;.;rtjynur6" | cat -e
1$
$>./hidenp "abc" "2altrb53c.sse" | cat -e
1$
$>./hidenp "abc" "btarc" | cat -e
0$
$>./hidenp | cat -e
$
$>
*/
#include <unistd.h>

char hidenp(char *str1, char *str2)
{
    while (*str2)
    {
        if (*str2 == *str1 && *str1)
        {
            str1++;
        }
        str2++;
    }
    if (*str1 == '\0')
        return ('1');
    return ('0');
}

int main(int argc, char *argv[])
{
    char result;
    if (argc == 3)
        result = hidenp(argv[1], argv[2]);
    write(1, &result, 1);
    write(1, "\n", 1);
    return (0);
}
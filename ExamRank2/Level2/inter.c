/*
Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Examples:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$
*/
#include <unistd.h>

void    inter(char *s, char *f)
{
    int seen[256] = {0};
    int i = 0;
    while (*s)
    {
        i = 0;
        while (f[i])
        {
            if (f[i] == *s && seen[(int)f[i]] == 0)
            {
                write(1, s, 1);
                seen[(int)f[i]] = 1;
                break ;
            }
            i++;
        }
        s++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
        inter(argv[1], argv[2]);
    write(1, "\n", 1);
    return (0);
}
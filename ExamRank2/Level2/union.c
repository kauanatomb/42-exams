/*
Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>
*/

#include <unistd.h>
void ft_union(char *str, char *str2)
{
    int seen[256] = {0};
    while(*str)
    {
        if (seen[(int)*str] == 0)
        {
            seen[(int)*str] = 1;
            write(1, str, 1);
        }
        str++;
    }
    while(*str2)
    {
        if (seen[(int)*str2] == 0)
        {
            seen[(int)*str2] = 1;
            write(1, str2, 1);
        }
        str2++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
        ft_union(argv[1], argv[2]);
    write(1, "\n", 1);
    return (0);
}
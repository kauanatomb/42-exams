/*
Write a program that takes a string and displays it, replacing each of its
letters by the letter 13 spaces ahead in alphabetical order.

'z' becomes 'm' and 'Z' becomes 'M'. Case remains unaffected.

The output will be followed by a newline.

If the number of arguments is not 1, the program displays a newline.

Example:

$>./rot_13 "abc"
nop
$>./rot_13 "My horse is Amazing." | cat -e
Zl ubefr vf Nznmvat.$
$>./rot_13 "AkjhZ zLKIJz , 23y " | cat -e
NxwuM mYXVWm , 23l $
$>./rot_13 | cat -e
$
$>
$>./rot_13 "" | cat -e
$
$>
*/

#include <unistd.h>

void    replace_w(char *str)
{
    while (*str)
    {
        if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z'))
        {
            if ((*str >= 'N' && *str <= 'Z') || (*str >= 'n' && *str <= 'z'))
                *str -= 13;
            else if ((*str >= 'A' && *str <= 'M') || (*str >= 'a' && *str <= 'm'))
                *str += 13;
        }
        write(1, str, 1);
        str++;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        replace_w(argv[1]);
    write(1, "\n", 1);
    return (0); 
}
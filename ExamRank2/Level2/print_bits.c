/*
Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"
*/
#include <unistd.h>

void	print_bits(unsigned char octet)
{
    unsigned char bit = 0;
    int i = 8;
    while (i--)
    {
        bit = (octet >> i & 1) + 48;
        write(1, &bit, 1);
    }
}

int main(void)
{
    print_bits(2);
    return (0);
}
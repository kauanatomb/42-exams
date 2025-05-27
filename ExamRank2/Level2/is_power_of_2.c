/*
Write a function that determines if a given number is a power of 2.

This function returns 1 if the given number is a power of 2, otherwise it returns 0.

Your function must be declared as follows:

int	    is_power_of_2(unsigned int n);
*/

int	    is_power_of_2(unsigned int n)
{
    if (n == 1)
        return (1);
    if (n % 2 != 0 || n == 0)
        return (0);
    return (is_power_of_2(n /2));
}

// #include <stdio.h>
// #include <limits.h>

// int main()
// {
//     printf("0 -> %d\n", is_power_of_2(0));      // 0
//     printf("1 -> %d\n", is_power_of_2(1));      // 1
//     printf("2 -> %d\n", is_power_of_2(2));      // 1
//     printf("3 -> %d\n", is_power_of_2(3));      // 0
//     printf("16 -> %d\n", is_power_of_2(16));    // 1
//     printf("INT_MAX -> %d\n", is_power_of_2(INT_MAX)); // 0
//     return (0);
// }

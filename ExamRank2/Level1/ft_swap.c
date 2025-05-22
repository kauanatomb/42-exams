/*
Write a function that swaps the contents of two integers the adresses of which
are passed as parameters.

Your function must be declared as follows:

void	ft_swap(int *a, int *b);
*/

void	ft_swap(int *a, int *b)
{
    int tmp = 0;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
/*

#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 5;
    ft_swap(&a, &b);
    printf("%d, %d", a, b);
}
*/
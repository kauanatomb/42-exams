/*
Write the following function:

void sort_int_tab(int *tab, unsigned int size);

It must sort (in-place) the 'tab' int array, that contains exactly 'size'
members, in ascending order.

Doubles must be preserved.

Input is always coherent.
*/

void sort_int_tab(int *tab, unsigned int size)
{
    int swap;
    unsigned int i =0;
    while (i < size - 1)
    {
        if (*tab && tab[i] > tab[i + 1])
        {
            swap = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = swap;
            i = 0;
        }
        else
            i++;
    }
}
#include <stdio.h>
int main()
{
    int i = 0;
    int tab[] = {3, 1, 2, 4, 6, 5};
    sort_int_tab(tab, 6);
    while (i < 6)
        printf("%d\n", tab[i++]);
    return (0);
}
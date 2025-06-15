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
    unsigned i = 0;
    while (i < size - 1)
    {
        if (tab[i] > tab[i + 1])
        {
            int tmp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = tmp;
            i = 0;
        }
        else
            i++;
    }
}
#include <stdio.h>
int main()
{
    int arr[] = {7, 3, 5, 9, 4, 2, 11};
    unsigned int size = 7;
    sort_int_tab(arr, size);
    unsigned int i = 0;
    while(size > i)
    {
        printf("%d\n", arr[i]);
        i++;
    }
    return (0);
}
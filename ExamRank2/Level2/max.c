/*
Write the following function:

int		max(int* tab, unsigned int len);

The first parameter is an array of int, the second is the number of elements in
the array.

The function returns the largest number found in the array.

If the array is empty, the function returns 0.
*/

int		max(int* tab, unsigned int len)
{
    int i = 0;
    int result = 0;
    if (!tab || len == 0)
        return (0);
    while (0 < len)
    {
        if (tab[i] > result)
            result = tab[i];
        i++;
        len--;
    }
    return (result);
}

// #include <stdio.h>

// int main(void)
// {
//     int arr[] = {1, 6, 10, 4, 11, 3, 11, 23, 0, 1, 32};
//     printf("%d", max(arr, 11));
//     return (0);
// }
/*
Write the following function:

int     *ft_range(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at start and end at end (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 1, 2 and 3.
- With (-1, 2) you will return an array containing -1, 0, 1 and 2.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing 0, -1, -2 and -3.
*/

#include <stdlib.h>
int     *ft_range(int start, int end)
{
    int *range;
    int i = 0;
    int count = (start <= end) ? end - start + 1 : start - end + 1;
    range = malloc(count * sizeof(int));
    if (!range)
        return (NULL);
    while (i < count)
    {
        range[i] = (start <= end) ? start + i : start - i;
        i++;
    }
    return (range);
}

// #include <stdio.h>
// int main(void)
// {
//     int start = 0;
//     int end = -3;
//     int *arr = ft_range(start, end);
//     if (!arr)
//         return (1);
//     int count = (start <= end) ? end - start + 1 : start - end + 1;
//     for (int i = 0; i < count; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
//     free(arr);
//     return (0);
// }
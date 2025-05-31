/*
Write the following function:

int     *ft_rrange(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at end and end at start (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 3, 2 and 1
- With (-1, 2) you will return an array containing 2, 1, 0 and -1.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing -3, -2, -1 and 0.
*/

#include <stdlib.h>
int     *ft_rrange(int start, int end)
{
    int size = (start < end) ? end - start + 1 : start - end + 1;
    int *range;
    int i = 0;
    range = malloc(sizeof(int) * size);
    if (!range)
        return (NULL);
    while (size > i)
    {
        range[i] = (start < end) ? end - i : end + i;
        i++;
    }
    return (range);
}

#include <stdio.h>
int main()
{
    int start = 0;
    int end = -3;
    int size = (start < end) ? end - start + 1 : start - end + 1;
    int *arr = ft_rrange(start, end);
    if (!arr)
        return (1);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    free(arr);
    return (0);
}
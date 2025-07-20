#include <stdio.h>
#include <stdlib.h>

void    print_set(int *set, int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%d%s", set[i], i == size - 1 ? "\n" : " ");
        i++;
    }
}

void    backtrack(int *nums, int size, int index, int *set, int set_len, int sum, int target)
{
    if (size == index)
    {
        if (sum == target)
            print_set(set, set_len);
        return ;
    }
    set[set_len] = nums[index];
    backtrack(nums, size, index + 1, set, set_len + 1, sum + nums[index], target);
    backtrack(nums, size, index + 1, set, set_len, sum, target);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    int target = atoi(argv[1]);
    int size = argc - 2;
    int *nums = malloc(sizeof(int) * size);
    int *set = malloc(sizeof(int) * size);
    if (!nums || !set)
    {
        if (set) free(set);
        if (nums) free(nums);
        return 1;
    }
    int i = 0;
    while (i < size)
    {
        nums[i] = atoi(argv[i + 2]);
        i++;
    }
    backtrack(nums, size, 0, set, 0, 0, target);
    free(nums);
    free(set);
    return 0;
}
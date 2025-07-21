#include <stdlib.h>
#include <stdio.h>

void print_set(int *set, int size)
{
    int i = 0;
    while(i < size)
    {
        printf("%d%s", set[i], i == size-1 ? "\n" : " ");
        i++;
    }
}

void backtrack(int *nums, int index, int size, int *set, int len_set, int sum, int target)
{
    if (index == size)
    {
        if (sum == target)
            print_set(set, len_set);
        return ;
    }
    set[len_set] = nums[index];
    backtrack(nums, index + 1, size, set, len_set + 1, sum + nums[index], target);
    backtrack(nums, index + 1, size, set, len_set, sum, target);
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
    backtrack(nums, 0, size, set, 0, 0, target);
    free(nums);
    free(set);
    return 0;
}
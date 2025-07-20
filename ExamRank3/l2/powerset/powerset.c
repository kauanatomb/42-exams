#include <stdio.h>
#include <stdlib.h>

void    print_set(int *set, int len)
{
    int i = 0;
    while (i < len)
    {
        printf("%d%s", set[i], i == len - 1 ? "\n" : " ");
        i++;
    }
}

void backtrack(int *nums, int n, int index, int target, int *set, int set_len, int sum)
{
    if (index == n)
    {
        if (sum == target)
            print_set(set, set_len);
        return ;
    }
    set[set_len] = nums[index];
    backtrack(nums, n, index + 1, target, set, set_len + 1, sum + nums[index]);
    backtrack(nums, n, index + 1, target, set, set_len, sum);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    int target = atoi(argv[1]);
    int n = argc - 2;
    int *nums = malloc(sizeof(int) * n);
    int *set = malloc(sizeof(int) * n);
    if (!nums || !set)
    {
        if (nums) free(nums);
        if (set) free(set);
        return 1;
    }
    int i = 0;
    while (i < n)
    {
        nums[i] = atoi(argv[i + 2]);
        i++;
    }
    backtrack(nums, n, 0, target, set, 0, 0);
    free(nums);
    free(set);
}
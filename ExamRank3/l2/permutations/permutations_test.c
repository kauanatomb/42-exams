#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sort(char *s)
{
    int i = 0;
    while (s[i])
    {
        int j = i + 1;
        while (s[j])
        {
            if (s[i] > s[j])
            {
                char tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void print_set(char *s)
{
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

void backtrack(char *s, int size, int *used, char *perm, int depth)
{
    if (size == depth)
    {
        perm[depth] = '\0';
        print_set(perm);
        return ;
    }
    int i = 0;
    while (i < size)
    {
        if (!used[i])
        {
            used[i] = 1;
            perm[depth] = s[i];
            backtrack(s, size, used, perm, depth + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;
    int n = strlen(argv[1]);
    int *used = calloc(sizeof(int), n);
    char *perm = malloc(n + 1);
    if (!used || !perm)
    {
        if (used) free(used);
        if (perm) free(perm);
        return 1;
    }
    sort(argv[1]);
    backtrack(argv[1], n, used, perm, 0);
    free(used);
    free(perm);
}
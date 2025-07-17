#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void    sort(char *s)
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

void    putline(char *s)
{
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

void    backtrack(char *s, int len, int *used, char *perm, int depth)
{
    if (len == depth)
    {
        perm[len] = '\0';
        putline(perm);
        return ;
    }
    int i = 0;
    while (i < len)
    {
        if (!used[i])
        {
            used[i] = 1;
            perm[depth] = s[i];
            backtrack(s, len, used, perm, depth + 1);
            used[i] = 0;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);
    sort(argv[1]);
    int len = strlen(argv[1]);
    int *used = calloc(len, sizeof(int));
    char *perm = malloc(len + 1);
    backtrack(argv[1], len, used, perm, 0);
    free(used);
    free(perm);
    return 0;
}
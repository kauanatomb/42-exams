/*
Write the following functions:

t_list	*sort_list(t_list* lst, int (*cmp)(int, int));

This function must sort the list given as a parameter, using the function
pointer cmp to select the order to apply, and returns a pointer to the
first element of the sorted list.

Duplications must remain.

Inputs will always be consistent.

You must use the type t_list described in the file list.h
that is provided to you. You must include that file
(#include "list.h"), but you must not turn it in. We will use our own
to compile your assignment.

Functions passed as cmp will always return a value different from
0 if a and b are in the right order, 0 otherwise.

For example, the following function used as cmp will sort the list
in ascending order:

int ascending(int a, int b)
{
	return (a <= b);
}
*/

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

int ascending(int a, int b)
{
	return (a <= b);
}

void    swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list *tmp = lst;
    while (lst && lst->next)
    {
        if (cmp(*(int *)lst->data, *(int *)lst->next->data) == 0)
        {
            swap((int *)lst->data, (int *)lst->next->data);
            lst = tmp;
        }
        else
            lst = lst->next;
    }
    return (tmp);
}
#include <stdio.h>
int main()
{
    int a = 9;
    int b = 3;
    int c = 5;
    t_list node3 = {NULL, &c};
    t_list node2 = {&node3, &b};
    t_list node = {&node2, &a};
    t_list *sorted = sort_list(&node, ascending);
    while (sorted)
    {
        printf("%d", *(int *)sorted->data);
        sorted = sorted->next;
    }
    return (0);
}
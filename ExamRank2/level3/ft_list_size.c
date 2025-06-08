/*
Write a function that returns the number of elements in the linked list that's
passed to it.

It must be declared as follows:

int	ft_list_size(t_list *begin_list);

You must use the following structure, and turn it in as a file called
ft_list.h:

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;
*/

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

int	ft_list_size(t_list *begin_list)
{
    int i = 0;
    while (begin_list)
    {
        i++;
        begin_list = begin_list->next;
    }
    return (i);
}

#include <stdio.h>
int main()
{
    t_list node3 = {NULL, "Node 3"};
    t_list node2 = {&node3, "Node 2"};
    t_list node1 = {&node2, "Node 1"};

    printf("List size: %d\n", ft_list_size(&node1)); // Should print 3
    return (0);
}
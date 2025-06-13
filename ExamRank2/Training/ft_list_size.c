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

int ft_list_size(t_list *begin_list)
{
    int count = 0;
    while (begin_list)
    {
        count++;
        begin_list = begin_list->next;
    }
    return (count);
}
#include <stdio.h>
int main()
{
    t_list node3 = {NULL, "Node3"};
    t_list node2 = {&node3, "Node2"};
    t_list node1 = {&node2, "Node1"};
    printf("%d", ft_list_size(&node1));
    return (0);
}
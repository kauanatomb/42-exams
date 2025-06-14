/*
Write a function that takes a list and a function pointer, and applies this
function to each element of the list.

It must be declared as follows:

void    ft_list_foreach(t_list *begin_list, void (*f)(void *));

The function pointed to by f will be used as follows:

(*f)(list_ptr->data);

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

void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    if (!begin_list || !f)
        return ;
    t_list *tmp = begin_list;
    while (tmp)
    {
        f(tmp->data);
        tmp = tmp->next;
    }
}
#include <stdio.h>
void    print_node(void *node)
{
    printf("%s\n", (char *)node);
}

int main()
{
    t_list node3 = {NULL, "Node3"};
    t_list node2 = {&node3, "Node2"};
    t_list nodes = {&node2, "Node"};
    ft_list_foreach(&nodes, print_node);
    return (0);
}
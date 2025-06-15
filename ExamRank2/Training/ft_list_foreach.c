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
    while (begin_list)
    {
        f(begin_list->data);
        begin_list = begin_list->next;
    }
}
#include <stdio.h>
void    print_node(void *s)
{
    printf("%s", (char *)s);
}

int main()
{
    t_list node = {NULL, "Node"};
    t_list node2= {&node, "Node1"};
    ft_list_foreach(&node2, print_node);
    return (0);
}
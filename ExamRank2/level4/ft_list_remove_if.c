/*
Write a function called ft_list_remove_if that removes from the
passed list any element the data of which is "equal" to the reference data.

It will be declared as follows :

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

cmp takes two void* and returns 0 when both parameters are equal.

You have to use the ft_list.h file, which will contain:

$>cat ft_list.h
typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;
$>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    if (!begin_list || !*begin_list)
        return ;
    t_list *tmp = *begin_list;
    if (cmp(data_ref, (*begin_list)->data) == 0)
    {
        *begin_list = tmp->next;
        free(tmp);
        ft_list_remove_if(begin_list, data_ref, cmp);
    }
    else
        ft_list_remove_if(&(*begin_list)->next, data_ref, cmp);
}

// t_list *create_elem(char *data)
// {
//     t_list *new = malloc(sizeof(t_list));
//     new->data = data;
//     new->next = NULL;
//     return new;
// }

// void print_list(t_list *head)
// {
//     while (head)
//     {
//         printf("%s -> ", (char *)head->data);
//         head = head->next;
//     }
//     printf("NULL\n");
// }

// int cmp(void *a, void *b)
// {
//     return strcmp((char *)a, (char *)b);
// }


// int main(void)
// {
//     t_list *list = create_elem("42");
//     list->next = create_elem("Paris");
//     list->next->next = create_elem("42");
//     list->next->next->next = create_elem("Piscine");

//     printf("Before:\n");
//     print_list(list);

//     ft_list_remove_if(&list, "42", cmp);

//     printf("After remove \"42\":\n");
//     print_list(list);

//     return (0);
// }
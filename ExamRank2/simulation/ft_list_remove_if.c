/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:05:44 by ktombola          #+#    #+#             */
/*   Updated: 2025/06/16 18:13:38 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_list
{
	struct s_list	*next;
	void		*data;
}			t_list;
#include <stdlib.h>
/*
#include "ft_list.h"
*/
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *tmp;
	while (*begin_list)
	{
		if (cmp((*begin_list)->data, data_ref) == 0)
		{
			tmp = *begin_list;
			*begin_list = (*begin_list)->next;
			free(tmp);
		}
		else
			*begin_list = (*begin_list)->next;
	}
}

int main()
{
	return (0);
}

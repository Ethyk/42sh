/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 16:23:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/21 14:18:50 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_simple_lst_add(t_list **first, t_list *new_node)
{
	if (new_node)
	{
		if (first == NULL || *first == NULL)
			*first = new_node;
		else
		{
			new_node->next = *first;
			*first = new_node;
		}
	}
}

void	ft_double_lst_add(t_lst_head **head, t_list_d *new_node)
{
	if (new_node)
	{
		if ((*head)->first)
		{
			new_node->next = (*head)->first;
			(*head)->first->prev = new_node;
			(*head)->first = new_node;
			(*head)->shift_middle -= 1;
			(*head)->node_count += 1;
		}
		else
		{
			(*head)->node_count += 1;
			(*head)->first = new_node;
			(*head)->middle = new_node;
		}
	}
	ft_lst_replace_middle(head);
}

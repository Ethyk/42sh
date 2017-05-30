#include "libft.h"
#include "list.h"

void	ft_simple_lst_pushback(t_list **first, t_list *new_node)
{
	t_list	*tmp;
	t_list	*old_tmp;

	if (new_node)
	{
		tmp = *first;
		while (tmp)
		{
			old_tmp = tmp;
			tmp = tmp->next;
		}
		old_tmp->next = new_node;
	}
}

void	ft_double_lst_pushback(t_lst_head **head, t_list_d *new_node)
{
	t_list_d	*prev;

	if (new_node)
	{
		prev = (*head)->last;
		new_node->prev = prev;
		prev->next = new_node;
		(*head)->last = new_node;
		(*head)->shift_middle += 1;
		(*head)->node_count += 1;
	}
	ft_lst_replace_middle(head);
}
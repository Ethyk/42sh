/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:11:45 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/22 18:11:56 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int	int_putchar(int c)
{
	ft_putchar((char)c);
	return (0);
}

void	put_termcap(char *capacity)
{
	tputs(tgetstr(capacity, NULL), 1, int_putchar);
}

void	put_ntermcap(char *capacity, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		put_termcap(capacity);
		i++;
	}
}

void	goto_termcap(char *capacity, int co, int li)
{
	tputs(tgoto(tgetstr(capacity, NULL), co, li), 1, int_putchar);
}
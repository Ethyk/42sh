/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:03:24 by seddaoud          #+#    #+#             */
/*   Updated: 2017/10/23 12:05:59 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_parrnew(void)
{
	void	**arr;

	arr = (void**)ft_memalloc(sizeof(void*));
	*arr = (void*)0;
	return (arr);
}
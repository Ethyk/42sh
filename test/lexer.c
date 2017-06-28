/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 12:22:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/28 13:57:47 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "color.h"
#include "lexer.h"
#include "parser.h"

/*
**	Going to send a line to the lexer and print the output top to bottom (last
**	token first)
*/

int		main(void)
{
	char	buff[4096];
	t_token	*token;
	t_lexer	lex;
	t_ast	*ast;
	
	ft_putstr("Give me a string > ");
	read(0, buff, 4096);
	*strchr(buff, '\n') = 0;
	if (strchr(buff, '\n') != NULL)
		printf(RED"Found a newline in the buff\n"RESET);
	lex = init_lexer(buff);
	ast = start_lex(&lex);
	while (lex.stack)
	{
		token = lex.stack->data;
		printf(MAG"#"CYN"%s"MAG"#"RESET, token->value);
		printf(" --> ");
		printf("type is %d", token->type);
		printf(" --> ");
		printf("id is %d\n", token->id);
		lex.stack = lex.stack->next;
	}
	return (0);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 23:50:05 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "color.h"
#include "libft.h"
#include "exec.h"
#include "printf.h"

/*
**	As a token is considered to be a leaf of the tree, the tree is being built
**	from the leaves to the root. Upon reading, tokens are converted into the
**	AST's nodes. Some nodes merely represent a symbol from our grammar, and do
**	not hold a token. The function fill_simple_command takes the full
**	list of tokens, and a temporary root to build upon. This temporary root is
**	considered to be a `simple command'.  The function will create a node, that
**	will act as a temporary root for our tree. For each token it reads from the
**	list:
**	- If the token is a WORD (not an operator ?)
**
**		A node will be created from that token by the function
**		ast_create_node_from_word. The node's symbol should be determined
**		according to the POSIX STANDARD's rules. This node will then be
**		appended to the child list of the current root node.
**
**	- If the token is an operator
**		- If the token is a redirection / an IO_NUMBER
**
**			A node representing an IO_REDIRECT should be created from every
**			token belonging to the redirection. This node will not hold any
**			token and will then be appended to the child list of the
**			current root node.
**
**		- If the token is a separator
**
**			The function stops, and stack pointer goes back to ast_parse,
**			bulding a new branch for the new command, and attaching the simple
**			command we just created to a complexe one.
*/

t_pipe	*create_pipe(int *p)
{
	t_pipe	*new;

	if (!p)
		return (NULL);
	new = ft_memalloc(sizeof(*new));
	new->p = p;
	return (new);
}

/*
**	This function starts the creation of the tree's branch.
*/

void	add_last_pipe(t_lst_head **head)
{
	t_pipe	*spipe;

	spipe = NULL;
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(spipe));
	else
	{
		ft_double_lst_pushback(head, ft_double_lst_create(NULL));
		(*head)->middle = (*head)->first;
	}
}

void	add_pipe(t_token *token, t_lst_head **head)
{
	t_pipe	*spipe;
	int		*p;

	spipe = NULL;
	p = NULL;
	if (ft_strequ(token->value, "|"))
	{
		p = palloc(sizeof(*p) * 2);
		pipe(p);
	}
	spipe = create_pipe(p);
	if (*head == NULL)
		*head = ft_create_head(ft_double_lst_create(spipe));
	else
		ft_double_lst_pushback(head, ft_double_lst_create(spipe));
}

t_ast	*ast_parse(t_ast *root, t_list **token_list, t_lst_head **head)
{
	int		command_name;
	t_token *token;
	t_ast	*ast;

	ast = root;
	command_name = 0;
	if (token_list && *token_list)
	{
		token = (*token_list)->data;
		if (TK_IS_SEP(token->id))
		{
			if ((ast = start_complexe_command(ast, token_list, \
							&command_name)) == NULL)
				return (NULL);
			add_pipe(token, head);
		}
		else if ((ast = create_simple_command(token_list)) == NULL)
			return (NULL);
		if ((ast = ast_parse(ast, token_list, head)) == NULL)
			return (NULL);
	}
	else
		add_last_pipe(head);
	return (ast);
}

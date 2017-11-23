#include "exec.h"
#include "hash_table.h"
#include "expand.h"
#include "builtin.h"
#include "failure.h"
#include "local.h"
#include "job_control.h"

/*
**	cmd_suffix       :            io_redirect
**	                 | cmd_suffix io_redirect
**	                 |            WORD
**	                 | cmd_suffix WORD
*/

int	exec_cmd_suffix(t_ast *ast, t_list **redirect_list, char ***av)
{
	t_ast	*io_redirect;
	t_ast	*word;
	char	**word_expanded;

	word = NULL;
	io_redirect = NULL;
	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_WORD))
		word = ast->child[0];
	else if (is_token(ast->child[1], TK_WORD))
		word = ast->child[1];
	if (word)
	{
		word_expanded = word_expansion(word->token->value, 0);
		*av = *av ? ft_arrayjoin_free(word_expanded, *av, 0b11) : word_expanded;
	}
	if (io_redirect)
		if (!(exec_io_redirect(io_redirect, redirect_list)))
			return (0);
	if (is_symb(ast->child[0], CMD_SUFFIX))
		return (exec_cmd_suffix(ast->child[0], redirect_list, av));
	return (1);
}

/*
**	cmd_prefix       :            io_redirect
**	                 | cmd_prefix io_redirect
**	                 |            ASSIGNMENT_WORD
**	                 | cmd_prefix ASSIGNMENT_WORD
**	                 ;
*/

void	exec_assignment_word(t_ast *ast)
{
	char		**word_expanded = NULL;
	char		*eq_pos;
	
	eq_pos = ft_strchr(ast->token->value, '=');
	word_expanded = word_expansion(eq_pos + 1, NO_GLOBBING | NO_FIELDSPLITING);
	if (word_expanded[0])
	{
		//fprintf(stderr, "word expanded\n");
		*eq_pos = 0;
		local_add_change_from_key_value(singleton_env(), ast->token->value, word_expanded[0]);
		*eq_pos = '=';
	}
	else
		local_add_change_from_string(singleton_env(), ast->token->value);
	ft_arraydel(&word_expanded);
}

int	exec_cmd_prefix(t_ast *ast, t_list **redirect_list)
{
	t_ast	*assignement_word = NULL;
	t_ast	*io_redirect = NULL;

	if (is_symb(ast->child[0], IO_REDIRECT))
		io_redirect = ast->child[0];
	else if (is_symb(ast->child[1], IO_REDIRECT))
		io_redirect = ast->child[1];
	if (is_token(ast->child[0], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[0];
	else if (is_token(ast->child[1], TK_ASSIGNMENT_WORD))
		assignement_word = ast->child[1];
	if (assignement_word)
		exec_assignment_word(assignement_word);
	if (io_redirect)
		if (!(exec_io_redirect(io_redirect, redirect_list)))
			return (0);
	if (is_symb(ast->child[0], CMD_PREFIX))
		return (exec_cmd_prefix(ast->child[0], redirect_list));
	return (1);

}

char	*extract_word(t_ast *ast)
{
	return (ft_strdup(ast->token->value));
}

char	**get_cmd_name(t_ast *ast, int flag)
{
	char 	*word = NULL;

	if (is_symb(ast->child[1], CMD_WORD))
		word = ast->child[1]->child[0]->token->value;
	else if (is_symb(ast->child[0], CMD_NAME))
		word = ast->child[0]->child[0]->token->value;
	return (word ? word_expansion(word, flag): NULL);
}

/*
**	simple_command   : cmd_prefix cmd_word cmd_suffix
**	                 | cmd_prefix cmd_word
**	                 | cmd_prefix
**	                 | cmd_name cmd_suffix
**	                 | cmd_name
*/

int		layer_command_suffix(t_ast *ast, char ***av, t_list	**redirect_list)
{
	t_ast	*cmd_suffix;
	char	**av_cmdsuffix;

	cmd_suffix = NULL;
	av_cmdsuffix = NULL;
	*av = get_cmd_name(ast, 0);
	if (is_symb(ast->child[1], CMD_SUFFIX))
		cmd_suffix = ast->child[1];
	if (is_symb(ast->child[2], CMD_SUFFIX))
		cmd_suffix = ast->child[2];
	if (cmd_suffix)
	{
		if (!exec_cmd_suffix(cmd_suffix, redirect_list, &av_cmdsuffix))
			return (EXIT_FAILURE);
		if (av_cmdsuffix)
			*av = *av ? ft_arrayjoin_free(*av, av_cmdsuffix, 0b11) : av_cmdsuffix;
	}
	return (EXIT_SUCCESS);
}

int		exec_simple_command(t_ast *ast)
{
	char	**av = NULL;
	t_list	*redirect_list = NULL;
	t_lst_func	*fct = NULL;
	int			exit_status = EXIT_SUCCESS;

	if (is_symb(ast->child[0], CMD_PREFIX))
	{
		if (!(exec_cmd_prefix(ast->child[0], &redirect_list)))
			return (EXIT_FAILURE);
	}
	if (layer_command_suffix(ast, &av, &redirect_list) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (av && av[0])
	{
		if ((fct = get_function(singleton_env(), av[0])))
			exit_status = exec_function(fct->fct_body, av);
		else if (get_exec_builtin(av[0]))
			exit_status = exec_builtin(singleton_env(), (const char **)av);
		else
			exec_bin(singleton_env(), (const char **)av);
		ft_arraydel(&av);
	}
	close_dup(redirect_list);
	return (exit_status);
}

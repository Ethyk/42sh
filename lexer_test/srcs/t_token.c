#include "libft.h"
#include "t_token.h"

/*
**	Creates a token, allocating memory for it and the string it contains,
**	storing many infos about the token.
*/

t_token		*create_token(const char *source, ssize_t *info)
{
	t_token		*token;
	size_t		size;

	token = ft_memalloc(sizeof(*token) * 1);
	size = info[_T_END] - info[_T_START] + 1;
	token->value = ft_strsub(source, info[_T_START], size);
	token->delim = source[info[_T_END] + 1];
	token->state_info = info;
	token->id = -1;
	return (token);
}

void		free_token(void *value)
{
	t_token *token;

	if (!value)
		return ;
	token = (t_token*)value;
	free(token->value);
	free(token->state_info);
	free(token);
}

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "t_env.h"
#include "exec.h"
#include "glob.h"
#include "expand.h"

/*  after "`" */
int		parse_backtick (t_expand *exp, int quoted)
{
	t_word comm;
	w_newword (&comm);

	while (exp->words[exp->offset])
	{
		if (exp->words[exp->offset] == '`')
		{
#ifdef EXPAND_DEBUG
			dprintf(2, exp->words[exp->offset]);
#endif
			exec_comm (comm.str, exp, quoted);
			return 0;
		}
		else
			w_addchar (&comm, exp->words[exp->offset]);
		++(exp->offset);
	}
	w_free (&comm);
	return WRDE_SYNTAX;
}

#include "line_editing.h"
#include "history.h"
#include "builtin.h"

/*
**	When CTRL-D is read, if the line is empty :
**	- if we're on the main LE, exit.
**	- if we're on heredoc LE, terminate le, return line->buff.
**
**	If line isnt empty, delete, delete char under the cursor if it exists.
*/

int		control_d(t_line *line)
{
	char	*command[] = {"exit", NULL};

	if (line->len == 0)
	{
		history_write_to_histfile();
		ft_putchar('\n');
		builtin_exit(singleton_env(), (const char **)command);
	}
	return (edit_del(line));
}

char	*control_d_heredoc(t_line *line)
{
	edit_add(4, line);
	return (edit_exit(line));
}

#include "line_editing.h"

void	move_cursor_lastline(t_line *line)
{
	cursor_goto_buff(line, line->len, line->pos);
	put_termcap("cr");
}

void	move_cursor_lastline_from_first_line(t_line *line)
{
	cursor_goto_buff(line, line->len, 0);
	put_termcap("cr");
}

void	move_cursor_firstline_from_lastline(t_line *line)
{
	cursor_goto_buff(line, 0, line->len);
	put_termcap("cr");
}

void	move_cursor_firstline_from_prev_pos(t_line *line)
{
	cursor_goto_buff(line, 0, line->old_pos);
	put_termcap("cr");
}

void	move_cursor_bufflen_from_lastline(t_line *line)
{
	cursor_goto_buff(line, line->len, line->pos);
}

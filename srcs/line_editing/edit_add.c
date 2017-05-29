#include "line_editing.h"

void	edit_add(int keycode, t_line *line)
{
	if (line->pos == line->len)
		line->buff[line->len] = (char)keycode;
	else
	{
		ft_memmove((void*)(line->buff + line->pos + 1), (void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	}
	line->pos++;
	line->len++;
}

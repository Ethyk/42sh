#include "line_editing.h"
#include "completion.h"
#include "history.h"
#include "failure.h"

static t_edit_func	g_edit_func[] =
{
	{KEY_LEFT, &edit_left},
	{KEY_RIGHT, &edit_right},
	{KEY_ALT_RIGHT, &edit_word_right},
	{KEY_ALT_LEFT, &edit_word_left},
	{KEY_ALT_UP, &edit_up},
	{KEY_ALT_DOWN, &edit_down},
	{KEY_HOME, &edit_home},
	{KEY_END, &edit_end},
	{KEY_BACKSPACE, &edit_backspace},
	{KEY_ALT_C, &copy},
	{KEY_ALT_V, &enter_visual_mode},
	{KEY_ALT_P, &paste},
	{KEY_CTRL_D, &control_d},
	{0, NULL}
};

/*
**	Calls the routine corresponding to the keycode. If the keycode doesnt
**	correspond to a command, it is simply appended to the buffer. (and will be
**	printed next time a refresh is called).
*/

int		edit_loop(unsigned long long keycode, t_line *line)
{
	int	i;

	i = 0;
	while (g_edit_func[i].keycode)
	{
		if (g_edit_func[i].keycode == keycode)
		{
			keycode = g_edit_func[i].f(line);
		}
		i++;
	}
	if (ft_isprint((char)keycode))
		edit_add(keycode, line);
	return (1);
}

/*
**	The function which starts the line editing, sets up the signals. Receives
**	the keycode from history_move_loop(). Enters a loop in which each keycode
**	is sent to edit_loop(), where it will be treated. If keycode is KEY_ENTER,
**	editing is complete, and the line is returned. Every time is key is
**	pressed, the displayed line is refreshed.
*/

char	*edit_get_input(void)
{
	unsigned long	keycode;
	t_line			*l;

	l = singleton_line();
	l->sig_handler();
	while (42)
	{
		l->old_pos = l->pos;
#ifdef COOR_DEBUG
		t_line *line = l;
		t_coor	pos;
		char	c = line->buff[line->pos];

		pos = get_char_visual_coor(line, line->pos);
		logwrite(__func__, "Line->buff["YEL"%d"RESET"] = "MAG"#"CYN"%c"MAG"#"RESET" @ {"PNK"%d "RESET";"PNK"%d"RESET"}\n", line->pos, c, pos.x, pos.y);
#endif
		keycode = 0;
		read(0, &keycode, 1);
		if (keycode == KEY_CTRL_D && l->heredoc && l->len == 0)
			return (control_d_heredoc(l));
		if (keycode == 27 || keycode > 127)
			read(0, (char *)&keycode + 1, 7);
		if (keycode != KEY_ALT_UP && keycode != KEY_ALT_DOWN)
			l->col_target = -1;
		if (btsearch_get_input(l, keycode))
			continue ;
		if (comple_get_input(l, keycode))
			continue ;
		if (keycode == KEY_ENTER)
			return (edit_exit(l));
		if (history_get_input(l, keycode))
			continue ;
		edit_loop(keycode, l);
	}
	return (NULL);
}

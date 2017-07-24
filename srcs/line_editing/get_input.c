#include "line_editing.h"
#include "completion.h"
#include "history.h"

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
	{KEY_ALT_R, &btsearch_get_input},
	//{KEY_SHIFT_UP},
	//{KEY_SHIFT_DOWN},
	{KEY_TAB, comple_get_input},
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
	line->old_pos = line->pos;
	while (g_edit_func[i].keycode)
	{
		if (g_edit_func[i].keycode == keycode)
		{
			g_edit_func[i].f(line);
			return (1);
		}
		i++;
	}
	if (ft_isprint((char)keycode) && keycode != KEY_DELETE)
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

char	*edit_get_input(t_env *env)
{
	unsigned long	keycode;
	t_line			*l;

	l = singleton_line();
	edit_set_signals();
	keycode = 0;
	while (42)
	{
		keycode = history_move_loop(l);
		if (keycode == KEY_ENTER)
			return (edit_exit(l));
		edit_loop(keycode, l);
		edit_refresh(l);
	}
	(void)env;
	return (NULL);
}
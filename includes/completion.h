/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:08:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 19:48:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H
# include "line_editing.h"
# include <dirent.h>

typedef struct	s_comple
{
	char		**matches;
	int			pos;
	int			signum;
	size_t		ws_col;
	size_t		ws_row;
	size_t		max_len;
	size_t		nb_lines;
	size_t		nb_colones;
	size_t		nb_matches;
	char		*to_replace;
	char		*current_word;
}				t_comple;

t_comple		*singleton_comple(void);

typedef struct	s_comple_func
{
	unsigned long long	keycode;
	int					(*f)(t_comple *);
}				t_comple_func;
/*
** signaux
*/
char			**comple_matching(t_line *line, t_comple *c);
void			comple_set_signals(void);
void			comple_handle_sigwinch(int signum);
void			comple_handle_sigint(int signum);

int				comple_init(t_line *line, t_comple *c);
int				comple_init_winch(t_comple *c);
int				comple_get_input(t_line *line, int keycode);
char			**comple_file_matches(t_line *line, t_comple *c);
char			*extract_color(char *str);
char			**comple_bin_matches(t_line *line, t_comple *c);

int				comple_right(t_comple *c);
int				comple_left(t_comple *c);
int				comple_up(t_comple *c);
int				comple_down(t_comple *c);

int				comple_refresh(t_line *line, t_comple c);

void			comple_clear(t_comple c);
void			comple_free(t_comple c);
int				comple_exit_matched(t_line *line, t_comple c,
		unsigned long long keycode);

char			*get_word_slash(t_line *line);
char			*get_start_word_cursor(t_line *line);
void			delete_word(char *to_replace);
char			*get_current_word_cursor(t_line *line);
#endif

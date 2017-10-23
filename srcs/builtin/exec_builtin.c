/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:51 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/23 15:11:08 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtin.h"
#include "exec.h"
#include "read.h"
#include <sys/wait.h>
#include <fcntl.h>
/*
**{"unset", &builtin_unset},
**{"set", &builtin_set},
*/

static t_builtin	g_builtin[] =
{
	{"cd", &builtin_cd},
	{"exit", &builtin_exit},
	{"env", &builtin_env},
	{"unsetenv", &builtin_unsetenv},
	{"setenv", &builtin_setenv},
	{"echo", &builtin_echo},
	{"alias", &builtin_alias},
	{"unalias", &builtin_unalias},
	{"read", &builtin_read},
	{"set", &builtin_set},
	{"unset", &builtin_unset},
	{NULL, NULL}
};

void		*get_exec_builtin(const char **argv)
{
	int			i;

	i = 0;
	while (g_builtin[i].key && !ft_strequ(g_builtin[i].key, argv[0]))
		i++;
	return (g_builtin[i].f);
}

int			exec_builtin(t_env *env, const char **argv, t_lst_head *head)
{
	int			(*f)(t_env*, const char**);

	(void)head;
	if ((f = get_exec_builtin(argv)) == NULL)
		return (0);
	env->previous_exit = f(env, argv);
	return (1);
}

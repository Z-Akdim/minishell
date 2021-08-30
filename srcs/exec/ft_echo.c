/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:14 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:16 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	ft_exec_echo(t_mini *m)
{
	m->v.j = 0;
	if ((ft_strncmp(m->args[m->v.i], "-n", 2) == 0)
	&& m->v.deja == 0)
	{
		m->v.j++;
		while (m->args[m->v.i][m->v.j] == 'n')
			m->v.j++;
		if (m->args[m->v.i][m->v.j] == '\0')
			m->v.i++;
		else
			m->v.n = 1;
		while ((ft_strcmp(m->args[m->v.i], "-n") == 0))
			m->v.i++;
		m->v.deja = 1;
	}
	m->v.j = 0;
	ft_putstr_fd(&m->args[m->v.i][m->v.j], 1);
	if (m->v.i + 1 < m->args_num)
		ft_putstr_fd(" ", 1);
}

void	ft_echo(t_mini *m)
{
	m->v.i = 1;
	m->v.j = 0;
	m->v.deja = 0;
	m->v.n = 0;
	g_v.exit_status = 0;
	if (!m->args[1])
		ft_putstr_fd("\n", 1);
	else
	{
		if ((ft_strcmp(m->args[1], "-n") == 0 && m->args[2])
		|| (ft_strcmp(m->args[1], "-n") != 0 && m->args[1]))
		{
			while (m->args[m->v.i])
			{
				ft_exec_echo(m);
				m->v.i++;
			}
		}
		if ((ft_strncmp(m->args[1], "-n", 2) != 0
		&& m->redirection_nocommand == 0) || m->v.n == 1)
			ft_putstr_fd("\n", 1);
	}
}

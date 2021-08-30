/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:21:47 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:21:50 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_is_alphanum(char c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z') ||
	(c >= '0' && c <= '9')) && c != 92)
		return (1);
	return (0);
}

void		ft_do_if_2(t_mini *m, int i)
{
	if (i == 0)
	{
		m->d.s_quotes = 1;
		m->d.new_line[m->d.j] = m->m_cmd[m->d.ret][m->d.i];
		m->d.j++;
		m->d.i++;
	}
	else if (i == 1)
	{
		m->d.s_quotes = 0;
		m->d.new_line[m->d.j] = m->m_cmd[m->d.ret][m->d.i];
		m->d.j++;
		m->d.i++;
	}
}

void		ft_do_if(t_mini *m, int i)
{
	ft_do_if_2(m, i);
	if (i == 2)
	{
		if (m->m_cmd[m->d.ret][m->d.i + 1] >= '0' &&
		m->m_cmd[m->d.ret][m->d.i + 1] <= '9')
			m->d.i += 2;
		else if (m->m_cmd[m->d.ret][m->d.i + 1] == '?')
			ft_do_if_3(m);
		else if (ft_is_alphanum(m->m_cmd[m->d.ret][m->d.i + 1]))
		{
			ft_get_dollar_value_1(m);
			ft_get_line_value(m);
		}
	}
}

void		ft_run_dollar(t_mini *m)
{
	if (m->m_cmd[m->d.ret][m->d.i] == 39 && m->d.s_quotes == 0)
		ft_do_if(m, 0);
	if (m->m_cmd[m->d.ret][m->d.i] == 39 && m->d.s_quotes == 1)
		ft_do_if(m, 1);
	if (((m->m_cmd[m->d.ret][m->d.i] == '$' &&
	m->m_cmd[m->d.ret][m->d.i - 1] != 92) ||
	(m->m_cmd[m->d.ret][m->d.i] == '$' && m->m_cmd[m->d.ret][m->d.i - 1] == 92
	&& m->m_cmd[m->d.ret][m->d.i - 2] == 92)) && m->d.s_quotes == 0)
		ft_do_if(m, 2);
	if (m->m_cmd[m->d.ret][m->d.i] == 92 && m->m_cmd[m->d.ret][m->d.i - 1]
	!= 92 && m->m_cmd[m->d.ret][m->d.i + 1] == '$' && m->d.s_quotes == 0)
		m->d.i++;
	if (m->m_cmd[m->d.ret][m->d.i] != '$' || (m->m_cmd[m->d.ret][m->d.i]
	== '$' && !ft_is_alphanum(m->m_cmd[m->d.ret][m->d.i + 1])) ||
	(m->m_cmd[m->d.ret][m->d.i] == '$' && m->m_cmd[m->d.ret][m->d.i - 1]
	== 92) || (m->m_cmd[m->d.ret][m->d.i] == '$' && m->d.s_quotes == 1))
	{
		m->d.new_line[m->d.j] = m->m_cmd[m->d.ret][m->d.i];
		m->d.i++;
		m->d.j++;
	}
}

void		ft_dollar_test(t_mini *m, int i)
{
	m->d.ret = i;
	ft_dollar_init(m);
	while (m->m_cmd[m->d.ret][m->d.i])
		ft_run_dollar(m);
	m->d.new_line[m->d.j] = '\0';
	free(m->m_cmd[m->d.ret]);
	m->m_cmd[m->d.ret] = NULL;
	m->m_cmd[m->d.ret] = ft_strdup(m->d.new_line);
	free(m->d.new_line);
	m->d.new_line = NULL;
}

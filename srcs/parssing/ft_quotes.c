/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:43 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:46 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_quotes_1(t_mini *m)
{
	if (((m->args[m->v.i][m->v.j] == 34 && m->v.i_d_q == 0 &&
	m->args[m->v.i][m->v.j - 1] != 92) ||
	(m->args[m->v.i][m->v.j] == 34 &&
	m->v.i_d_q == 0 && m->args[m->v.i][m->v.j - 1] == 92 &&
	m->args[m->v.i][m->v.j - 2] == 92)) && (m->v.i_s_q == 0))
	{
		m->v.i_d_q = 1;
		m->v.j++;
	}
	if (m->args[m->v.i][m->v.j] == 34 && m->v.i_d_q == 1)
	{
		m->v.i_d_q = 0;
		m->v.j++;
	}
	if (((m->args[m->v.i][m->v.j] == 39 && m->v.i_s_q == 0 &&
	m->args[m->v.i][m->v.j - 1] != 92) ||
	(m->args[m->v.i][m->v.j] == 39 &&
	m->v.i_s_q == 0 && m->args[m->v.i][m->v.j - 1] == 92 &&
	m->args[m->v.i][m->v.j - 2] == 92)) && (m->v.i_d_q == 0))
	{
		m->v.i_s_q = 1;
		m->v.j++;
	}
}

void		ft_quotes_2_1(t_mini *m)
{
	if (m->v.i_d_q == 1)
		if (m->args[m->v.i][m->v.j] == 92)
			if ((m->args[m->v.i][m->v.j + 1] == 92
			|| m->args[m->v.i][m->v.j + 1] == 34
			|| (ft_nb_antislash(m->args[m->v.i]) == 1 &&
			m->args[m->v.i][m->v.j + 1] != '$')) &&
			(ft_sp_char(m->args[m->v.i][m->v.j + 1]) == 1))
				m->v.j++;
}

void		ft_quotes_2(t_mini *m)
{
	m->v.block_copy = 0;
	if (m->args[m->v.i][m->v.j] == 39 && m->v.i_s_q == 1)
	{
		m->v.i_s_q = 0;
		m->v.j++;
	}
	ft_quotes_2_1(m);
	if (m->args[m->v.i][m->v.j] == 92 && m->args[m->v.i]
	[m->v.j + 1] != '$' && m->v.i_d_q == 0 && m->v.i_s_q == 0)
		m->v.j++;
	if ((m->args[m->v.i][m->v.j] == 39 && m->args[m->v.i]
	[m->v.j - 1] != 92 && m->v.i_d_q == 0) || (m->args[m->v.i]
	[m->v.j] == 34 && m->args[m->v.i][m->v.j - 1] != 92
	&& m->v.i_s_q == 0))
		m->v.block_copy = 1;
	if (m->v.block_copy == 0)
	{
		m->v.correct_args[m->v.c] = m->args[m->v.i][m->v.j];
		m->v.c++;
		m->v.j++;
	}
}

void		ft_init_quotes(t_mini *m)
{
	m->v.i_d_q = 0;
	m->v.i_s_q = 0;
	m->v.j = 0;
	m->v.i = 0;
	m->v.c = 0;
	m->v.block_copy = 0;
	m->v.correct_args = NULL;
}

int			ft_quotes(t_mini *m)
{
	ft_init_quotes(m);
	while (m->args[m->v.i])
	{
		m->v.j = 0;
		m->v.c = 0;
		m->v.correct_args = malloc(sizeof(char) *
		(ft_strlen(m->args[m->v.i]) + 1));
		while (m->args[m->v.i][m->v.j])
		{
			ft_quotes_1(m);
			ft_quotes_2(m);
		}
		m->v.correct_args[m->v.c] = '\0';
		free(m->args[m->v.i]);
		m->args[m->v.i] = ft_strdup(m->v.correct_args);
		free(m->v.correct_args);
		m->v.correct_args = NULL;
		if (m->v.i_d_q == 1 || m->v.i_s_q == 1)
		{
			ft_error("syntax error multiline commands", "\n", "");
			return (-1);
		}
		m->v.i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:28 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:30 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int			ignore_qotes(char *str, int i)
{
	int count;

	count = 0;
	if (str[--i] == '\\')
	{
		count++;
		while (str[i] == '\\')
		{
			count++;
			i--;
		}
	}
	if (count % 2 == 0 && count != 0)
		return (0);
	else
		return (1);
}

int			ft_multiline_3(t_mini *m, int i, int count, int i_s_q)
{
	while (m->line[i])
	{
		if (m->line[i] == '\'' &&
		(ignore_qotes(m->line, i) == 1 || i_s_q == 1))
		{
			if (i_s_q)
				i_s_q = 0;
			else
				i_s_q = 1;
		}
		if (m->line[i] == 92 && m->line[i + 1] == 92 && i_s_q == 0)
		{
			while (m->line[i] == '\\')
			{
				count++;
				i++;
			}
		}
		else if (m->line[i + 1] == '\0' && i_s_q == 0 && m->line[i] == 92)
			return (12);
		i++;
	}
	if ((count % 2) != 0 && count != 0)
		return (12);
	return (0);
}

int			ft_syntax_error_1(t_mini *m, int i)
{
	if (m->line[0] == '|')
		return (5);
	if ((m->line[i] == '|' && m->line[i + 1] == ' ' &&
		m->line[i + 2] == '|') || (m->line[i] == '|' &&
		m->line[i + 1] == '|'))
		return (6);
	if ((m->line[i] == '<' || m->line[i] == '>') && !m->line[i + 1])
		return (7);
	if (m->line[i] == ';' && m->line[i + 1] == '|')
		return (8);
	if (m->line[i] == '|' && m->line[i + 1] == ';')
		return (9);
	if (m->line[0] == ';')
		return (10);
	return (0);
}

int			ft_syntax_error(t_mini *m, int i)
{
	if (ft_multiline_3(m, 0, 0, 0) == 12)
		return (12);
	while (m->line[i])
	{
		if ((m->line[i] == '>' && m->line[i + 1] == '>' &&
			m->line[i + 2] == '>' && m->line[i + 3] != '>') ||
			(m->line[i] == '>' && m->line[i + 1] == ' ' &&
			m->line[i + 2] == '>'))
			return (1);
		else if (m->line[i] == '>' && m->line[i + 1] == '>' &&
			m->line[i + 2] == '>' && m->line[i + 3] == '>')
			return (3);
		else if (m->line[i] == '>')
		{
			i++;
			while (m->line[i] == ' ' || m->line[i] == '\t')
				i++;
			if (m->line[i] == '<')
				return (2);
		}
		else if (m->line[i] == ';' && m->line[i + 1] == ';')
			return (4);
		i++;
	}
	return (0);
}

int			syn_error(t_mini *m, int i)
{
	i = ft_syntax_error(m, 0);
	if (i == 0)
		i = ft_syntax_error_1(m, i);
	if (i == 1)
		ft_error("syntax error near unexpected token ", "`>'", "\n");
	else if (i == 2)
		ft_error("syntax error near unexpected token ", "`<'", "\n");
	else if (i == 3)
		ft_error("syntax error near unexpected token ", "`>>'", "\n");
	else if (i == 4)
		ft_error("syntax error near unexpected token ", "`;;'", "\n");
	else if (i == 5 || i == 6)
		ft_error("syntax error near unexpected token ", "`|'", "\n");
	else if (i == 7)
		ft_error("syntax error near unexpected token ", "`newline'", "\n");
	else if (i == 8 || i == 10)
		ft_error("syntax error near unexpected token ", "`;'", "\n");
	else if (i == 9)
		ft_error("syntax error near unexpected token ", "`|'", "\n");
	else if (i == 12)
		ft_error("syntax error multiline commands", "\n", "");
	else if (i == 0)
		return (0);
	return (1);
}

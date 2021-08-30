/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_args_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:23:12 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:23:13 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_cpy_sort_arg(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (m->sort_args[i])
		i++;
	ft_free_args(m);
	m->args = malloc(sizeof(char *) * (i));
	i = 0;
	while (m->sort_args[i])
	{
		m->args[i] = ft_strdup(m->sort_args[i]);
		i++;
	}
	m->args[i] = NULL;
	ft_free_sort_args(m);
}

void		ft_sorte_args_1(t_mini *m)
{
	m->sort_args = malloc(sizeof(char *) * (m->args_num + 1));
	while (m->args[m->var.j] &&
	ft_strcmp(m->args[m->var.j], ">") != 0
	&& ft_strcmp(m->args[m->var.j], ">>") != 0
	&& ft_strcmp(m->args[m->var.j], "<") != 0)
	{
		m->sort_args[m->var.i] = ft_strdup(m->args[m->var.j]);
		m->var.j++;
		m->var.i++;
	}
	if (ft_strcmp(m->args[m->var.j], ">") == 0 ||
	ft_strcmp(m->args[m->var.j], ">>")
	== 0 || ft_strcmp(m->args[m->var.j], "<") == 0)
		m->var.index = m->var.j;
	m->var.j = 0;
	while (m->args[m->var.j] && m->var.j < 2)
	{
		m->sort_args[m->var.i] = ft_strdup(m->args[m->var.j]);
		m->var.j++;
		m->var.i++;
	}
}

void		ft_sorte_args(t_mini *m)
{
	m->var.i = 0;
	m->var.j = 2;
	m->var.index = -1;
	if ((ft_strcmp(m->args[0], ">") == 0 || ft_strcmp(m->args[0], ">>")
	== 0 || ft_strcmp(m->args[0], "<") == 0) && m->args[2])
	{
		ft_sorte_args_1(m);
		if (m->var.index != -1)
		{
			m->var.j = m->var.index;
			while (m->args[m->var.j])
			{
				m->sort_args[m->var.i] =
				ft_strdup(m->args[m->var.j]);
				m->var.j++;
				m->var.i++;
			}
		}
		m->sort_args[m->var.i] = NULL;
		ft_cpy_sort_arg(m);
	}
}

int			redirection_sorted_args(t_mini *m)
{
	int		i;

	i = 0;
	while (m->args[i])
	{
		if (m->args[i] && i != 0 && (ft_strcmp(m->args[i - 1], ">") == 0
		|| ft_strcmp(m->args[i - 1], ">>") == 0 ||
		ft_strcmp(m->args[i - 1], "<") == 0) && m->args[i + 1] &&
		(ft_strcmp(m->args[i + 1], ">") != 0 &&
		ft_strcmp(m->args[i + 1], ">>")
		!= 0 && ft_strcmp(m->args[i + 1], "<") != 0))
			return (0);
		if (!m->args[i])
			break ;
		i++;
	}
	return (1);
}

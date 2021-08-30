/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_args_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:23:22 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:23:24 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_cpy_sort_arg2(t_mini *m, int index)
{
	int i;

	i = 0;
	ft_free_args(m);
	m->args = malloc(sizeof(char *) * (index + 1));
	i = 0;
	while (m->sorted_args2[i])
	{
		m->args[i] = ft_strdup(m->sorted_args2[i]);
		i++;
	}
	m->args[i] = NULL;
	ft_free_sort_args2(m);
}

int			ft_num_args(t_mini *m)
{
	int i;
	int alloc;

	i = 0;
	alloc = 0;
	while (m->args[i])
	{
		if (m->args[i] && i != 0 &&
		ft_strcmp(m->args[i - 1], ">") == 0 && m->args[i + 1])
		{
			i++;
			while (m->args[i] && ft_strcmp(m->args[i], ">") != 0)
			{
				alloc++;
				i++;
			}
		}
		if (!m->args[i])
			break ;
		i++;
	}
	return (alloc);
}

void		ft_get_sort_args(t_mini *m, int i, int j)
{
	m->args_to_sort = (char **)malloc(sizeof(char *)
	* (ft_num_args(m) + 1));
	while (m->args[i])
	{
		if (m->args[i] && i != 0 && (ft_strcmp(m->args[i - 1], ">") == 0
		|| ft_strcmp(m->args[i - 1], ">>") == 0 ||
		ft_strcmp(m->args[i - 1], "<") == 0) && m->args[i + 1])
		{
			i++;
			while (m->args[i] && ft_strcmp(m->args[i], ">") != 0)
			{
				m->args_to_sort[j] = ft_strdup(m->args[i]);
				free(m->args[i]);
				m->args[i] = ft_strdup("NON");
				i++;
				j++;
			}
		}
		if (!m->args[i])
			break ;
		i++;
	}
	m->args_to_sort[j] = NULL;
}

void		ft_sort_args2_1(t_mini *m)
{
	while (m->args[m->v.i])
		m->v.i++;
	m->sorted_args2 = malloc(sizeof(char *) * (m->v.i + 1));
	m->v.i = 0;
	while (m->args[m->v.i] && ft_strcmp(m->args[m->v.j], ">") != 0
	&& ft_strcmp(m->args[m->v.j], ">>") != 0 &&
	ft_strcmp(m->args[m->v.j], "<") != 0)
	{
		m->sorted_args2[m->v.i] = ft_strdup(m->args[m->v.j]);
		m->v.i++;
		m->v.j++;
	}
	m->sorted_args2[m->v.i] = NULL;
	m->v.index = m->v.i;
	m->v.j = 0;
	while (m->args_to_sort[m->v.j])
	{
		m->sorted_args2[m->v.i] =
		ft_strdup(m->args_to_sort[m->v.j]);
		m->v.i++;
		m->v.j++;
	}
}

void		ft_sort_args2(t_mini *m)
{
	m->v.i = 0;
	m->v.j = 0;
	if (redirection_sorted_args(m) == 0)
	{
		ft_get_sort_args(m, 0, 0);
		ft_sort_args2_1(m);
		while (m->args[m->v.index])
		{
			if (ft_strcmp(m->args[m->v.index], "NON") == 0
			&& m->args[m->v.i])
				while (ft_strcmp(m->args[m->v.index], "NON") == 0)
					m->v.index++;
			if (!m->args[m->v.i])
				break ;
			m->sorted_args2[m->v.i] =
			ft_strdup(m->args[m->v.index]);
			m->v.i++;
			m->v.index++;
		}
		m->sorted_args2[m->v.i] = NULL;
		ft_cpy_sort_arg2(m, m->v.i);
		ft_free_args_to_sort(m);
	}
}

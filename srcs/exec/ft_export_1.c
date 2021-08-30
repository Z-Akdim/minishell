/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:25 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:26 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_sort_table(t_mini *m)
{
	int				i;
	char			*tmp;
	int				size;

	i = 0;
	size = 0;
	while (m->envp_g[size])
		size++;
	while (i < size)
	{
		if (m->export.tab[i + 1] != NULL &&
		ft_strcmp(m->export.tab[i], m->export.tab[i + 1]) > 0)
		{
			tmp = ft_strdup(m->export.tab[i]);
			free(m->export.tab[i]);
			m->export.tab[i] = NULL;
			m->export.tab[i] = ft_strdup(m->export.tab[i + 1]);
			free(m->export.tab[i + 1]);
			m->export.tab[i + 1] = NULL;
			m->export.tab[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = -1;
		}
		i++;
	}
}

void		ft_run_export_1(t_mini *m, int i)
{
	m->v.index = 1;
	free(m->envp_g[m->v.j]);
	m->envp_g[m->v.j] = NULL;
	free(m->v.arg);
	m->v.arg = NULL;
	m->v.arg = ft_strdup(m->args[i]);
	m->envp_g[m->v.j] = ft_strdup(m->v.arg);
}

void		ft_run_export_2(t_mini *m, int i)
{
	while (m->envp_g[m->v.j])
	{
		if (m->envp_g[m->v.j] &&
		ft_strncmp(m->envp_g[m->v.j], m->v.arg,
		ft_strlen(m->v.arg)) == 0 &&
		ft_equal_check(m->args[i]) == 0)
		{
			g_v.exit_status = 0;
			m->v.index = 5;
			break ;
		}
		m->v.j++;
	}
	if (m->v.index != 5)
	{
		g_v.exit_status = 0;
		ft_strjoin2(m, m->args[i]);
	}
}

void		ft_run_export(t_mini *m, int i)
{
	m->v.j = 0;
	m->v.index = 0;
	while (m->args[i][m->v.j] && m->args[i][m->v.j] != '=')
		m->v.j++;
	m->v.arg = ft_strlcpy(m->v.arg, m->args[i], m->v.j);
	while (m->envp_g[m->v.j])
	{
		if (m->envp_g[m->v.j] &&
		ft_strncmp(m->envp_g[m->v.j],
		m->v.arg, ft_strlen(m->v.arg)) == 0 &&
		ft_equal_check(m->args[i]) == 1)
		{
			g_v.exit_status = 0;
			ft_run_export_1(m, i);
			break ;
		}
		m->v.j++;
	}
	m->v.j = 0;
	if (m->v.index == 0)
		ft_run_export_2(m, i);
	free(m->v.arg);
}

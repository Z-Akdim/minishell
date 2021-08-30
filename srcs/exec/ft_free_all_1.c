/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:37 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:39 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_free_sort_args2(t_mini *m)
{
	int i;

	i = 0;
	while (m->sorted_args2[i])
	{
		free(m->sorted_args2[i]);
		m->sorted_args2[i] = NULL;
		i++;
	}
	if (m->sorted_args2)
		free(m->sorted_args2);
}

void		ft_free_path_1(t_mini *m, int i)
{
	while (m->add_path[i])
	{
		free(m->add_path[i]);
		m->add_path[i] = NULL;
		i++;
	}
	if (m->add_path)
		free(m->add_path);
	i = 0;
	while (m->add_path1[i])
	{
		free(m->add_path1[i]);
		m->add_path1[i] = NULL;
		i++;
	}
	if (m->add_path1)
		free(m->add_path1);
}

void		ft_free_path(t_mini *m)
{
	int i;

	i = 0;
	if (m->free_path == 1)
	{
		ft_free_path_1(m, i);
		if (m->path)
		{
			free(m->path);
			m->path = NULL;
		}
	}
	if (m->free_run_path == 1)
	{
		if (m->run_path)
		{
			free(m->run_path);
			m->run_path = NULL;
		}
	}
}

void		ft_free_env(t_mini *m)
{
	int i;

	i = 0;
	while (m->envp_g[i])
	{
		free(m->envp_g[i]);
		m->envp_g[i] = NULL;
		i++;
	}
	if (m->envp_g)
		free(m->envp_g);
}

void		ft_free_export(t_mini *m)
{
	int i;

	i = 0;
	while (m->export.tab[i])
	{
		free(m->export.tab[i]);
		m->export.tab[i] = NULL;
		i++;
	}
	if (m->export.tab)
		free(m->export.tab);
}

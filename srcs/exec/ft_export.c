/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:31 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:33 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_export_1(t_mini *m)
{
	int		i;
	int		j;
	int		index;

	i = 1;
	j = 0;
	index = 0;
	while (m->args[i])
	{
		if ((m->args[i][0] >= 'a' && m->args[i][0] <= 'z') ||
		(m->args[i][0] >= 'A' && m->args[i][0] <= 'Z') ||
		(m->args[i][0] == '_'))
			ft_run_export(m, i);
		else
		{
			g_v.exit_status = 1;
			ft_error("bash: export: `",
			m->args[i], "': not a valid identifier\n");
		}
		i++;
	}
}

void		ft_copy_export(t_mini *m)
{
	int i;

	i = 0;
	while (m->envp_g[i])
		i++;
	m->export.tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (m->envp_g[i])
	{
		m->export.tab[i] = ft_strdup(m->envp_g[i]);
		i++;
	}
	m->export.tab[i] = NULL;
}

void		ft_copy_export2(t_mini *m)
{
	int i;

	i = 0;
	while (m->envp_g[i])
		i++;
	ft_free_export(m);
	m->export.tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (m->envp_g[i])
	{
		m->export.tab[i] = ft_strdup(m->envp_g[i]);
		i++;
	}
	m->export.tab[i] = NULL;
}

void		ft_export(t_mini *m, int i, int j)
{
	if (m->args[1])
		ft_export_1(m);
	else
	{
		ft_copy_export_with_quotes(m);
		ft_sort_table(m);
		i = 0;
		g_v.exit_status = 0;
		while (m->export.tab[i])
		{
			ft_putstr_fd("declare -x ", 1);
			j = 0;
			while (m->export.tab[i][j])
			{
				if (m->export.tab[i][j - 1] == '=')
					ft_putchar('"');
				ft_putchar(m->export.tab[i][j]);
				j++;
			}
			if (ft_equal_check(m->export.tab[i]) == 1)
				ft_putchar('"');
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
}

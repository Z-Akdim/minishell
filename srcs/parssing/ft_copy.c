/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:21:36 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:21:39 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int			ft_sp_char(char c)
{
	if (c == '"' || c == 92 || c == '$' || c == '`')
		return (1);
	return (0);
}

int			ft_nb_antislash(char *arg)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		if (arg[i] == 92)
			ret++;
		i++;
	}
	return (ret);
}

void		ft_copy_env(t_mini *m, char **envp)
{
	int		line;
	int		i;

	line = 0;
	i = 0;
	while (envp[line])
		line++;
	m->envp_g = malloc(sizeof(char *) * (line + 1));
	while (envp[i])
	{
		m->envp_g[i] = ft_strdup(envp[i]);
		i++;
	}
	m->envp_g[i] = NULL;
}

void		ft_copy_export_with_quotes_1(t_mini *m)
{
	while (m->envp_g[m->var.i][m->var.j])
	{
		if (m->envp_g[m->var.i][m->var.j - 1] == '=')
		{
			m->export.tab[m->var.i][m->var.n] = '"';
			m->var.n++;
		}
		m->export.tab[m->var.i][m->var.n] =
		m->envp_g[m->var.i][m->var.j];
		m->var.n++;
		m->var.j++;
		if (m->envp_g[m->var.i][m->var.j] == '\0' &&
		ft_equal_check(m->envp_g[m->var.i]) == 1)
		{
			m->export.tab[m->var.i][m->var.n] = '"';
			m->var.n++;
		}
	}
}

void		ft_copy_export_with_quotes(t_mini *m)
{
	int		line;

	line = 0;
	m->var.i = 0;
	m->var.n = 0;
	m->var.j = -1;
	while (m->envp_g[line])
		line++;
	ft_free_export(m);
	m->export.tab = malloc(sizeof(char *) * (line + 1));
	while (m->envp_g[m->var.i])
	{
		m->export.tab[m->var.i] = ft_strdup(m->envp_g[m->var.i]);
		m->var.i++;
	}
	m->export.tab[m->var.i] = NULL;
}

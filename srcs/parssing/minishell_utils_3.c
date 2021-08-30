/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:17 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:18 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void				ft_strjoin_export_2(t_mini *m, char *s2)
{
	while (m->export.tab[m->var.i])
		m->var.i++;
	m->var.s1 = malloc(sizeof(char *) * (m->var.i + 2));
	m->var.i = 0;
	while (m->export.tab[m->var.i])
	{
		m->var.s1[m->var.i] = ft_strdup(m->export.tab[m->var.i]);
		m->var.i++;
	}
	m->var.s1[m->var.i] = ft_strdup(s2);
	m->var.i++;
	m->var.s1[m->var.i] = NULL;
	ft_free_export(m);
	m->export.tab = malloc(sizeof(char *) * m->var.i + 1);
}

void				ft_strjoin_export(t_mini *m, char *s2)
{
	m->var.j = 0;
	m->var.index = 0;
	m->var.i = 0;
	ft_strjoin_export_2(m, s2);
	m->var.i = 0;
	while (m->var.s1[m->var.i])
	{
		m->export.tab[m->var.i] = ft_strdup(m->var.s1[m->var.i]);
		m->var.i++;
	}
	m->export.tab[m->var.i] = NULL;
	m->var.i = 0;
	while (m->var.s1[m->var.i])
	{
		free(m->var.s1[m->var.i]);
		m->var.s1[m->var.i] = NULL;
		m->var.i++;
	}
	if (m->var.s1)
		free(m->var.s1);
}

void				ft_strjoin2_1(t_mini *m, char *s2)
{
	while (m->envp_g[m->var.i])
		m->var.i++;
	m->var.s1 = malloc(sizeof(char *) * (m->var.i + 2));
	m->var.i = 0;
	while (m->envp_g[m->var.i])
	{
		m->var.s1[m->var.i] = ft_strdup(m->envp_g[m->var.i]);
		m->var.i++;
	}
	m->var.s1[m->var.i] = ft_strdup(s2);
	m->var.i++;
	m->var.s1[m->var.i] = NULL;
	ft_free_env(m);
	m->envp_g = malloc(sizeof(char *) * m->var.i + 1);
}

void				ft_strjoin2(t_mini *m, char *s2)
{
	m->var.j = 0;
	m->var.index = 0;
	m->var.i = 0;
	ft_strjoin2_1(m, s2);
	m->var.i = 0;
	while (m->var.s1[m->var.i])
	{
		m->envp_g[m->var.i] = ft_strdup(m->var.s1[m->var.i]);
		m->var.i++;
	}
	m->envp_g[m->var.i] = NULL;
	m->var.i = 0;
	while (m->var.s1[m->var.i])
	{
		free(m->var.s1[m->var.i]);
		m->var.s1[m->var.i] = NULL;
		m->var.i++;
	}
	if (m->var.s1)
		free(m->var.s1);
}

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	i = 0;
	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	while ((s11[i] || s22[i]) && i < n)
	{
		if (s11[i] != '\0' && s22[i] == '\0')
			return (s11[i]);
		if (s11[i] == '\0' && s22[i] != '\0')
			return (-s22[i]);
		if (s11[i] > s22[i])
			return (s11[i] - s22[i]);
		if (s11[i] < s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

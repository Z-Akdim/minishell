/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:22 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:24 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_get_path_2(t_mini *m)
{
	m->free_path = 1;
	while (m->envp_g[m->var.i][m->var.j] != '=')
		m->var.j++;
	m->var.j++;
	m->path = ft_strdup(&m->envp_g[m->var.i][m->var.j]);
	m->add_path = ft_split(m->path, ':');
	m->var.i = 0;
	m->var.tmp = ft_strjoin("/", m->args[0]);
	while (m->add_path[m->var.i])
		m->var.i++;
	m->add_path1 = malloc(sizeof(char *) * (m->var.i + 1));
	m->var.i = 0;
	while (m->add_path[m->var.i])
	{
		m->add_path1[m->var.i] =
		ft_strjoin(m->add_path[m->var.i], m->var.tmp);
		m->var.i++;
	}
}

void		ft_get_path(t_mini *m)
{
	struct stat buffer;

	m->var.i = 0;
	m->var.j = 0;
	m->free_path = 0;
	m->free_run_path = 0;
	while (m->envp_g[m->var.i + 1] &&
	strncmp(m->envp_g[m->var.i], "PATH=", 5) != 0)
		m->var.i++;
	if (strncmp(m->envp_g[m->var.i], "PATH=", 5) == 0)
	{
		ft_get_path_2(m);
		m->add_path1[m->var.i] = NULL;
		free(m->var.tmp);
		m->var.i = -1;
		while (m->add_path1[++m->var.i])
			if (stat(m->add_path1[m->var.i], &buffer) == 0)
			{
				m->free_run_path = 1;
				m->run_path = ft_strdup(m->add_path1[m->var.i]);
			}
	}
}

void		ft_check_home(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_strncmp(m->envp_g[i], "HOME=", 5) != 0 && m->envp_g[i + 1])
		i++;
	if (ft_strncmp(m->envp_g[i], "HOME=", ft_strlen("HOME=")) != 0)
		m->home_error = ft_strdup("ERROR");
	else
		m->home_error = ft_strdup("NO_ERROR");
}

void		ft_get_home_2(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_strncmp(m->envp_g[i], "HOME=", 5) != 0 && m->envp_g[i + 1])
		i++;
	if (ft_strncmp(m->envp_g[i], "HOME=", ft_strlen("HOME=")) == 0)
		m->home_two = &m->envp_g[i][5];
}

void		ft_get_home(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_strncmp(m->envp_g[i], "HOME=", 5) != 0 && m->envp_g[i + 1])
		i++;
	if (ft_strncmp(m->envp_g[i], "HOME=", ft_strlen("HOME=")) == 0)
		m->home = &m->envp_g[i][5];
}

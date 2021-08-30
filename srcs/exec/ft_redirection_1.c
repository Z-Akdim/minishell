/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:29 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:31 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_redirection_run_1(t_mini *m)
{
	m->std = 1;
	g_v.exit_status = 0;
	m->redirection_fd = open(m->input_file,
	O_RDWR | O_CREAT | O_TRUNC, 0777);
}

void		ft_redirection_run_2(t_mini *m)
{
	m->std = 1;
	g_v.exit_status = 0;
	m->redirection_fd = open(m->input_file,
	O_RDWR | O_CREAT | O_APPEND, 0777);
}

int			ft_redirection_run_3(t_mini *m)
{
	m->std = 0;
	m->redirection = 0;
	g_v.exit_status = 0;
	if ((m->redirection_fd = open(m->input_file,
	O_RDWR, 0777)) == -1)
	{
		ft_error(m->input_file, ": No such file or directory", "\n");
		free(m->input_file);
		free(m->v.type);
		m->redirection_error = 1;
		g_v.exit_status = 1;
		return (-1);
	}
	return (0);
}

void		ft_redirection(t_mini *m, int i)
{
	int			index;

	m->redirection = 1;
	index = i;
	while ((ft_strcmp(m->args[i], ">") == 0 ||
	ft_strcmp(m->args[i], ">>") == 0
	|| ft_strcmp(m->args[i], "<") == 0) && m->args[i])
	{
		m->v.type = ft_strdup(m->args[i]);
		i++;
		m->input_file = ft_strdup(m->args[i]);
		if (ft_strcmp(m->v.type, ">") == 0)
			ft_redirection_run_1(m);
		else if (ft_strcmp(m->v.type, ">>") == 0)
			ft_redirection_run_2(m);
		else if (ft_strcmp(m->v.type, "<") == 0)
			if (ft_redirection_run_3(m) == -1)
				return ;
		free(m->input_file);
		free(m->v.type);
		i++;
	}
	ft_free_args_redirection(m, index);
	dup2(m->redirection_fd, m->std);
}

int			ft_check_redirection(t_mini *m)
{
	int i;
	int j;

	i = 0;
	j = 0;
	m->redirection = 0;
	ft_redirection_nocommand(m);
	while (m->args[i])
	{
		m->std = -1;
		if (ft_strcmp(m->args[i], ">") == 0
		|| ft_strcmp(m->args[i], ">>") == 0
		|| ft_strcmp(m->args[i], "<") == 0)
			ft_redirection(m, i);
		if (m->redirection_error == 1)
			return (-1);
		i++;
	}
	return (0);
}

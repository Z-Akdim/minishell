/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:44 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:45 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_free_pipe_args(t_mini *m)
{
	int i;

	i = 0;
	while (m->pipe.args[i])
	{
		free(m->pipe.args[i]);
		m->pipe.args[i] = NULL;
		i++;
	}
	if (m->pipe.args)
		free(m->pipe.args);
}

void		ft_free_multi_command(t_mini *m)
{
	int i;

	i = 0;
	while (m->m_cmd[i])
	{
		free(m->m_cmd[i]);
		m->m_cmd[i] = NULL;
		i++;
	}
	if (m->m_cmd)
		free(m->m_cmd);
}

void		ft_free_args(t_mini *m)
{
	int i;

	i = 0;
	while (m->args[i])
	{
		free(m->args[i]);
		m->args[i] = NULL;
		i++;
	}
	if (m->args)
		free(m->args);
}

void		ft_free_echo_args(t_mini *m)
{
	int i;

	i = 0;
	while (m->echo.args[i])
	{
		free(m->echo.args[i]);
		i++;
	}
	if (m->echo.args)
		free(m->echo.args);
}

void		ft_free_sort_args(t_mini *m)
{
	int i;

	i = 0;
	while (m->sort_args[i])
	{
		free(m->sort_args[i]);
		i++;
	}
	if (m->sort_args)
		free(m->sort_args);
}

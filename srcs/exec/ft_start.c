/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:55 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:57 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_no_pipe(t_mini *m)
{
	ft_free_pipe_args(m);
	ft_free_args(m);
	ft_free_path(m);
}

int		ft_parss_run(t_mini *m, int i)
{
	ft_get_args(m);
	if (ft_quotes(m) == -1)
		return (-1);
	ft_sorte_args(m);
	ft_sort_args2(m);
	ft_check_args(m);
	ft_get_path(m);
	m->redirection_error = 0;
	if (ft_strcmp(m->args[0], "<") == 0 && i == 0)
		return (-2);
	return (0);
}

void	ft_free_start(t_mini *m, int i)
{
	ft_free_pipe_args(m);
	ft_free_args(m);
	if (i == 1)
		ft_free_path(m);
	if (i != 2)
		ft_free_multi_command(m);
}

int		ft_start_no_pipe(t_mini *m, int i)
{
	int error;

	error = ft_parss_run(m, i);
	if (error == -1 || error == -2)
	{
		if (error == -1)
			ft_free_start(m, 0);
		else if (error == -2)
			ft_free_start(m, 1);
		return (-1);
	}
	else if (ft_check_redirection(m) == -1)
	{
		ft_free_start(m, 1);
		return (-1);
	}
	return (0);
}

void	ft_start_minishell(t_mini *m, int i, int j)
{
	while (m->m_cmd[i] != NULL)
	{
		ft_dollar_test(m, i);
		while (m->m_cmd[i][j] <= 32 && m->m_cmd[i][j] > 126)
			j++;
		if (m->m_cmd[i][j])
		{
			m->check_pipe = 0;
			ft_check_pipe_command(m, i);
			free(m->line);
			m->line = ft_strdup(m->m_cmd[i]);
			if (m->check_pipe == 0)
				if (ft_start_no_pipe(m, i) == -1)
					return ;
			ft_start_minishell_2(m);
		}
		i++;
	}
	ft_free_multi_command(m);
}

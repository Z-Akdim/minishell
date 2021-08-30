/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:15 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:17 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_pipe(t_mini *m, int i)
{
	char	*new_multi_command;
	int		j;

	j = 0;
	m->pipe.args = ft_split(m->m_cmd[i], '|');
	while (m->pipe.args[j])
	{
		new_multi_command = ft_strdup(m->pipe.args[j]);
		free(m->pipe.args[j]);
		m->pipe.args[j] = ft_strtrim(new_multi_command, ' ');
		free(new_multi_command);
		j++;
	}
}

void		ft_get_pipe_args(t_mini *m, int k)
{
	int		i;

	i = -1;
	i = 0;
	m->args = ft_split(m->pipe.args[k], ' ');
	while (m->args[++i])
		;
	m->args_num = i;
}

void		ft_check_args(t_mini *m)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < m->args_num && m->args[i])
	{
		if ((m->args[i][0] == '~' && m->args[i][1] == '/') ||
		(m->args[i][0] == '~' && m->args[i][1] == '\0'))
		{
			tmp = ft_strdup(&m->args[i][1]);
			free(m->args[i]);
			m->args[i] = ft_strjoin(m->home, tmp);
			free(tmp);
		}
		i++;
	}
}

int			ft_get_args(t_mini *m)
{
	int		i;

	i = -1;
	m->args = ft_split(m->line, ' ');
	while (m->args[++i])
		;
	m->args_num = i;
	return (0);
}
